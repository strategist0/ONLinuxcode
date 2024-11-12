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
    if (sb->len + extra > sb->alloc) {
        size_t new_alloc = sb->alloc * 2;
        if (new_alloc < sb->len + extra) {
            new_alloc = sb->len + extra;
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

}
void strbuf_addstr(struct strbuf *sb, const char *s) 
{

}
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2) 
{

}
void strbuf_setlen(struct strbuf *sb, size_t len) 
{

}
size_t strbuf_avail(const struct strbuf *sb) 
{

}
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len) 
{

}
void strbuf_rtrim(struct strbuf *sb) 
{

}
void strbuf_ltrim(struct strbuf *sb) 
{

}
void strbuf_remove(struct strbuf *sb, size_t pos, size_t len) 
{

}
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint) 
{

}
int strbuf_getline(struct strbuf *sb, FILE *fp) 
{

}
struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max) 
{

}
bool strbuf_begin_judge(char *target_str, const char *str, int strnlen) 
{

}
char *strbuf_get_mid_buf(char *target_buf, int begin, int end, int len) 
{

}