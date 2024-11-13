#include <stdio.h>
#include <string.h>
#include "strbuf.h"

void strbuf_init(struct strbuf *sb, size_t alloc)
{
    sb->len = 0;
    sb->alloc = alloc;
    sb->buf = (char *)malloc(alloc);
    if (sb->buf) {
        sb->buf[0] = '\0';
    }
}
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc) 
{
    if (sb->buf != NULL) {
        free(sb->buf);
    }

    sb->buf = (char *)str;

    sb->len = len;
    sb->alloc = alloc;
}
void strbuf_release(struct strbuf *sb) 
{
    free(sb->buf);
    sb->len = 0;
    sb->alloc = 0;
    sb->buf = NULL;
}
void strbuf_swap(struct strbuf *a, struct strbuf *b) 
{
    char *tmp_buf = a->buf;
    a->buf = b->buf;
    b->buf = tmp_buf;

    size_t tmp_len = a->len;
    a->len = b->len;
    b->len = tmp_len;

    size_t tmp_alloc = a->alloc;
    a->alloc = b->alloc;
    b->alloc = tmp_alloc;
}
char *strbuf_detach(struct strbuf *sb, size_t *sz) 
{
    if(sz){
        *sz = sb->alloc;
    }

    char *detached_buf = sb->buf;
    sb->buf = NULL;
    sb->len = 0;
    sb->alloc = 0;
    return detached_buf;
}
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second) 
{
    if (first->len != second->len) {
        return first->len - second->len;
    }
    return memcmp(first->buf, second->buf, first->len);
}
void strbuf_reset(struct strbuf *sb) 
{
    sb->len = 0;
    if (sb->buf) {
        sb->buf[0] = '\0';
    }
}
void strbuf_grow(struct strbuf *sb, size_t extra) 
{
    if (sb->len + extra + 1 > sb->alloc) {
        size_t new_alloc = sb->alloc * 2;
        if (new_alloc < sb->len + extra + 1) { 
            new_alloc = sb->len + extra + 1;
        }

        char *new_buf = (char *)realloc(sb->buf, new_alloc);
        if (new_buf) {
            sb->buf = new_buf;
            sb->alloc = new_alloc;
        }
    }
}
void strbuf_add(struct strbuf *sb, const void *data, size_t len) 
{
    strbuf_grow(sb, len);
    memcpy(sb->buf + sb->len, data, len);
    sb->len += len;
    sb->buf[sb->len] = '\0';
}
void strbuf_addch(struct strbuf *sb, int c) 
{
    if (sb->len + 1 >= sb->alloc) {
        sb->alloc = sb->alloc ? sb->alloc * 2 : 16;
        sb->buf = (char *)realloc(sb->buf, sb->alloc);
    }
    sb->buf[sb->len++] = (char)c;
    sb->buf[sb->len] = '\0';
}
void strbuf_addstr(struct strbuf *sb, const char *s) 
{
    size_t slen = strlen(s);
    strbuf_grow(sb, slen);
    memcpy(sb->buf + sb->len, s, slen);
    sb->len += slen;
    sb->buf[sb->len] = '\0';
}
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2) 
{
    strbuf_grow(sb, sb2->len);
    memcpy(sb->buf + sb->len, sb2->buf, sb2->len);
    sb->len += sb2->len;
    sb->buf[sb->len] = '\0';
}
void strbuf_setlen(struct strbuf *sb, size_t len) 
{
    sb->len = len;
    if (sb->len < sb->alloc) {
        sb->buf[sb->len] = '\0';
    }
}
size_t strbuf_avail(const struct strbuf *sb) 
{
    return sb->alloc - sb->len - 1;
}
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len) 
{
    strbuf_grow(sb, len);
    memmove(sb->buf + pos + len, sb->buf + pos, sb->len - pos);
    memcpy(sb->buf + pos, data, len);
    sb->len += len;
    sb->buf[sb->len] = '\0';
}
void strbuf_rtrim(struct strbuf *sb) 
{
    size_t i = sb->len;

    while (i > 0 && (sb->buf[i - 1] == ' ' || sb->buf[i - 1] == '\t' || sb->buf[i - 1] == '\n' || sb->buf[i - 1] == '\r')) {
        i--;
    }

    if (i < sb->len) {
        sb->len = i;
        sb->buf[sb->len] = '\0';
    }
}
void strbuf_ltrim(struct strbuf *sb) 
{
    size_t i = 0;

    while (i < sb->len && (sb->buf[i] == ' ' || sb->buf[i] == '\t' || sb->buf[i] == '\n' || sb->buf[i] == '\r')) {
        i++;
    }

    if (i > 0) {
        memmove(sb->buf, sb->buf + i, sb->len - i);
        sb->len -= i;
        sb->buf[sb->len] = '\0';
    }
}
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len) 
{
    if (pos >= sb->len || len == 0) {
        return;
    }

    size_t end = pos + len;
    if (end > sb->len) {
        end = sb->len;
    }

    memmove(sb->buf + pos, sb->buf + end, sb->len - end);

    sb->len -= (end - pos);

    sb->buf[sb->len] = '\0';
}
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint) 
{
    size_t growth = hint ? hint : 8192;

    strbuf_grow(sb, growth);

    char buf[growth];
    ssize_t total_read = 0;

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0) {
        strbuf_add(sb, buf, bytes_read);
        total_read += bytes_read;
    }

    if (bytes_read < 0) {
        return -1;
    }

    return total_read;
}
int strbuf_getline(struct strbuf *sb, FILE *fp) 
{
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), fp) == NULL) {
        return -1;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    strbuf_addstr(sb, buffer);

    return 0;
}
struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max) 
{
    struct strbuf **result = malloc(sizeof(struct strbuf*) * (max + 1));
    size_t start = 0;
    int count = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] == terminator || (max > 0 && count == max - 1)) {

            struct strbuf *sb = malloc(sizeof(struct strbuf));
            strbuf_init(sb);
            strbuf_addstr(sb, &str[start]);
            result[count] = sb;
            count++;

            start = i + 1;
            if (count == max) {
                break;
            }
        }
    }

    if (start < len) {
        struct strbuf *sb = malloc(sizeof(struct strbuf));
        strbuf_init(sb);
        strbuf_addstr(sb, &str[start]);
        result[count] = sb;
    }

    result[count] = NULL;
    return result;
}
bool strbuf_begin_judge(char *target_str, const char *str, int strnlen) 
{

}
char *strbuf_get_mid_buf(char *target_buf, int begin, int end, int len) 
{

}