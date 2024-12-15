#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <limits.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define COLOR_RESET "\033[0m"
#define COLOR_DIR "\033[1;34m"
#define COLOR_EXEC "\033[1;32m"
#define COLOR_SYMLINK "\033[1;36m"

typedef struct {
  int show_all;
  int long_list;
  int recursive;
  int sort_time;
  int reverse;
  int show_inode;
  int show_blocks;
} Options;

typedef struct FileNode {
  char name[NAME_MAX + 1];
  struct stat statbuf;
  struct FileNode *next;
} FileNode;

void process_directory(const char *path, const Options *opts);
FileNode *add_file(FileNode *head, const char *name,
                   const struct stat *statbuf);
void free_file_list(FileNode *head);
void sort_files(FileNode **head, const Options *opts);
void print_file(const FileNode *file, const Options *opts);
void display_usage(const char *prog_name);

int main(int argc, char *argv[]) {
  Options opts = {0};
  char *target_dir = ".";

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      for (int j = 1; argv[i][j]; ++j) {
        switch (argv[i][j]) {
        case 'a':
          opts.show_all = 1;
          break;
        case 'l':
          opts.long_list = 1;
          break;
        case 'R':
          opts.recursive = 1;
          break;
        case 't':
          opts.sort_time = 1;
          break;
        case 'r':
          opts.reverse = 1;
          break;
        case 'i':
          opts.show_inode = 1;
          break;
        case 's':
          opts.show_blocks = 1;
          break;
        default:
          fprintf(stderr, "Unknown option: -%c\n", argv[i][j]);
          display_usage(argv[0]);
          return EXIT_FAILURE;
        }
      }
    } else {
      target_dir = argv[i];
    }
  }

  process_directory(target_dir, &opts);

  return 0;
}

void display_usage(const char *prog_name) {
  fprintf(stderr, "Usage: %s [-alRtirs] [directory]\n", prog_name);
}

FileNode *add_file(FileNode *head, const char *name,
                   const struct stat *statbuf) {
  FileNode *new_node = malloc(sizeof(FileNode));
  if (!new_node) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  strncpy(new_node->name, name, NAME_MAX);
  new_node->name[NAME_MAX] = '\0';
  new_node->statbuf = *statbuf;
  new_node->next = head;
  return new_node;
}

void free_file_list(FileNode *head) {
  while (head) {
    FileNode *temp = head;
    head = head->next;
    free(temp);
  }
}

void sort_files(FileNode **head, const Options *opts) {
  FileNode *sorted = NULL;

  while (*head) {
    FileNode *curr = *head;
    *head = (*head)->next;

    if (!sorted ||
        (opts->sort_time ? curr->statbuf.st_mtime > sorted->statbuf.st_mtime
                         : strcmp(curr->name, sorted->name) < 0)) {
      curr->next = sorted;
      sorted = curr;
    } else {
      FileNode *s = sorted;
      while (s->next &&
             (opts->sort_time
                  ? curr->statbuf.st_mtime <= s->next->statbuf.st_mtime
                  : strcmp(curr->name, s->next->name) >= 0)) {
        s = s->next;
      }
      curr->next = s->next;
      s->next = curr;
    }
  }

  *head = sorted;

  if (opts->reverse) {
    FileNode *prev = NULL, *curr = *head, *next = NULL;
    while (curr) {
      next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    *head = prev;
  }
}

void print_file(const FileNode *file, const Options *opts) {
  if (opts->show_inode) {
    printf("%10lu ", file->statbuf.st_ino);
  }
  if (opts->show_blocks) {
    printf("%5ld ", file->statbuf.st_blocks);
  }
  if (opts->long_list) {
    char perms[11] = "----------";
    if (S_ISDIR(file->statbuf.st_mode))
      perms[0] = 'd';
    if (S_ISLNK(file->statbuf.st_mode))
      perms[0] = 'l';
    if (file->statbuf.st_mode & S_IRUSR)
      perms[1] = 'r';
    if (file->statbuf.st_mode & S_IWUSR)
      perms[2] = 'w';
    if (file->statbuf.st_mode & S_IXUSR)
      perms[3] = 'x';
    if (file->statbuf.st_mode & S_IRGRP)
      perms[4] = 'r';
    if (file->statbuf.st_mode & S_IWGRP)
      perms[5] = 'w';
    if (file->statbuf.st_mode & S_IXGRP)
      perms[6] = 'x';
    if (file->statbuf.st_mode & S_IROTH)
      perms[7] = 'r';
    if (file->statbuf.st_mode & S_IWOTH)
      perms[8] = 'w';
    if (file->statbuf.st_mode & S_IXOTH)
      perms[9] = 'x';

    struct passwd *pw = getpwuid(file->statbuf.st_uid);
    struct group *gr = getgrgid(file->statbuf.st_gid);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M",
             localtime(&file->statbuf.st_mtime));

    printf("%s %4ld %-8s %-8s %8ld %s ", perms, file->statbuf.st_nlink,
           pw ? pw->pw_name : "UNKNOWN", gr ? gr->gr_name : "UNKNOWN",
           file->statbuf.st_size, time_str);
  }

  if (S_ISDIR(file->statbuf.st_mode)) {
    printf(COLOR_DIR "%s" COLOR_RESET, file->name);
  } else if (file->statbuf.st_mode & S_IXUSR) {
    printf(COLOR_EXEC "%s" COLOR_RESET, file->name);
  } else if (S_ISLNK(file->statbuf.st_mode)) {
    printf(COLOR_SYMLINK "%s" COLOR_RESET, file->name);
  } else {
    printf("%s", file->name);
  }
  printf("\n");
}

void process_directory(const char *path, const Options *opts) {
  DIR *dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return;
  }

  printf("\n%s:\n", path);
  struct dirent *entry;
  FileNode *file_list = NULL;

  while ((entry = readdir(dir))) {
    if (!opts->show_all && entry->d_name[0] == '.')
      continue;

    char full_path[PATH_MAX];
    snprintf(full_path, PATH_MAX, "%s/%s", path, entry->d_name);
    struct stat statbuf;
    if (lstat(full_path, &statbuf) == -1) {
      perror("lstat");
      continue;
    }
    file_list = add_file(file_list, entry->d_name, &statbuf);
  }
  closedir(dir);

  sort_files(&file_list, opts);

  for (FileNode *node = file_list; node; node = node->next) {
    print_file(node, opts);
  }

  free_file_list(file_list);

  if (opts->recursive) {
    dir = opendir(path);
    while ((entry = readdir(dir))) {
      if (entry->d_name[0] == '.')
        continue;

      char full_path[PATH_MAX];
      snprintf(full_path, PATH_MAX, "%s/%s", path, entry->d_name);

      struct stat statbuf;
      if (lstat(full_path, &statbuf) == -1) {
        perror("lstat");
        continue;
      }

      if (S_ISDIR(statbuf.st_mode)) {
        process_directory(full_path, opts);
      }
    }
    closedir(dir);
  }
}
