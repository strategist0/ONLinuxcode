#include <stdio.h>
#include <string.h>
#include "strbuf.h"

void strbuf_init(struct strbuf *sb, size_t alloc)
{
    sb->len = 0;
    sb->alloc = alloc;
    sb->buf = (char *)malloc(alloc);
    if(sb->buf){
        sb->buf[0] = '\0';
    }
}
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc)
{
    sb->len = len;
    sb->alloc = alloc;
    sb->buf = (char *)str;
    if(sb->buf){
        sb->buf[len] = '\0';
    }
}
void strbuf_release(struct strbuf *sb)
{
    sb->len = 0;
    sb->alloc = 0;
    free(sb->buf);
}
void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
    struct strbuf tmp = *a;
    a->alloc = b->alloc;
    a->len = b->len;
    a->buf = b->buf;
    b->alloc = tmp.alloc;
    b->len = tmp.len;
    b->buf = tmp.buf;
}
char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
    if(sz){
        *sz = sb->alloc;
    }
    char *str = sb->buf;
    sb->buf = NULL;
    sb->len = 0;
    sb->alloc = 0;
    return str;
}
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{         
    if(memcmp(first->buf, second->buf, first->len)){
        return 1;
    }
    else
    return 0;
}
void strbuf_reset(struct strbuf *sb)
{
    sb->buf[0] = NULL;
    sb->len = 0;
}
void strbuf_grow(struct strbuf *sb, size_t extra)
{
    if(sb->len + extra + 1 > sb->alloc){
        size_t nalloc = sb->alloc * 2;
        if(nalloc < sb->len + extra + 1){
            nalloc = sb->len + extra + 1;
        }
    
        char *nbuf = (char *)realloc(sb->buf, nalloc);
        if(nbuf){
            sb->buf = nbuf;
            sb->alloc = nalloc;
        }
    }
}
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
    if(sb->len + len + 1 > sb->alloc){
        size_t nalloc = (sb->len + len + 1) * 2;
        char *nbuf = (char *)malloc(nalloc);
        memcpy(nbuf, sb->buf, sb->len);
        free(sb->buf);
        sb->buf = nbuf;
        sb->alloc = nalloc;
    }
    memcpy(sb->buf + sb->len, data, len);
    sb->len += len;
    sb->buf[sb->len] = '\0';
}
void strbuf_addch(struct strbuf *sb, int c)
{
    if (sb->len + 1 >= sb->alloc) {
        sb->alloc = (sb->alloc == 0) ? 2 : sb->alloc * 2;
        sb->buf = (char *)realloc(sb->buf, sb->alloc); 
    }
    sb->buf[sb->len] = (char)c;
    sb->len++;
    sb->buf[sb->len] = '\0';
}
void strbuf_addstr(struct strbuf *sb, const char *s)
{
    size_t len = strlen(s);
    //void strbuf_add(struct strbuf *sb, const void *data, size_t len);
    if(sb->len + len + 1 > sb->alloc){
        size_t nalloc = (sb->len + len + 1) * 2;
        char *nbuf = (char *)malloc(nalloc);
        memcpy(nbuf, sb->buf, sb->len);
        free(sb->buf);
        sb->buf = nbuf;
        sb->alloc = nalloc;
    }
    memcpy(sb->buf + sb->len, s, len);
    sb->len += len;
    sb->buf[sb->len] = '\0';
}
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2)
{
    size_t len = sb2->len;
    size_t alloc = sb2->alloc;
    char *buf = sb2->buf;
    //void strbuf_add(struct strbuf *sb, const void *data, size_t len);
    //add用两回了(憋笑.jpg)
    if(sb->len + len + 1 > sb->alloc){
        size_t nalloc = (sb->len + len + 1) * 2;
        char *nbuf = (char *)malloc(nalloc);
        memcpy(nbuf, sb->buf, sb->len);
        free(sb->buf);
        sb->buf = nbuf;
        sb->alloc = nalloc;
    }
    memcpy(sb->buf + sb->len, buf, len);
    sb->len += len;
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
    //虽然不知道要写什么，但是我先放个add在这里()
    if(sb->len + len + 1 > sb->alloc){
        size_t nalloc = (pos + len + 1) * 2;
        char *nbuf = (char *)malloc(nalloc);
        memcpy(nbuf, sb->buf, pos);
        memcpy(nbuf + pos + len, sb->buf + pos, sb->len - pos);
        free(sb->buf);
        sb->buf = nbuf;
        sb->alloc = nalloc;
    }
    memmove(sb->buf + pos + len, sb->buf + pos, sb->len - pos);
    memcpy(sb->buf + pos, data, len);
    sb->len += len;
    sb->buf[sb->len] = '\0';
    //译演顶针，鉴定为add变体
}

void strbuf_rtrim(struct strbuf *sb)
{
    int end = sb->len - 1;
    if (sb->len == 0) {
        return;
    }
     while (end >= 0 && (sb->buf[end] == '\t' || sb->buf[end] == ' ' || sb->buf[end] == '\r' || sb->buf[end] == '\n')){
        end--;
    }
    sb->buf[end + 1] = '\0';
    sb->len = end + 1;
}
void strbuf_ltrim(struct strbuf *sb)
{
    int i = 0;
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
    memmove(sb->buf + pos, sb->buf + pos + len, sb->len - pos - len);
    sb->len -= len;
    sb->buf[sb->len] = '\0';
}
ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)
{
    size_t nalloc = hint ? hint : 8192;
    if(sb->alloc - sb->len < nalloc){
        nalloc = (sb->alloc + nalloc) * 2;
        sb->buf = (char *)realloc(sb->buf, nalloc);
        sb->alloc = nalloc;
    }
    ssize_t nread = read(fd, sb->buf + sb->len, sb->alloc - sb->len);
    if(nread > 0){
        sb->len += nread;
        sb->buf[sb->len] = '\0';
    }
    return nread;
}
int strbuf_getline(struct strbuf *sb, FILE *fp)
{
    if(sb->alloc - sb->len < 1){
        size_t nalloc = sb->alloc ? sb->alloc * 2 : 8192;
        sb->buf = (char *)realloc(sb->buf, nalloc);
        sb->alloc = nalloc;
    }
    size_t plen = sb->len;
    char c;
    while((c = fgetc(fp)) != EOF){
        if(c == '\n'){
            break;
        }
        sb->buf[sb->len++] = c;
        if(sb->len + 1 >= sb->alloc){
            sb->alloc *= 2;
            sb->buf = (char *)realloc(sb->buf, sb->alloc);
        }
    }
    sb->buf[sb->len] = '\0';
    return sb->len - plen;
}
struct strbuf **strbuf_split_buf(const char *str, size_t len, int terminator, int max)
{
    
}
bool strbuf_begin_judge(char *target_str, const char *str, int strnlen)
{
    int i = 0;
    while(i < strnlen && str[i] != '\0'){
        if(target_str[i] != str[i]){
            return false;
        }
        i++;
    }
    if(i = strnlen - 1){
        return true;
    }
}
char *strbuf_get_mid_buf(char *target_buf, int begin, int end, int len)
{
    if (!target_buf || begin < 0 || end > len || begin > end) {
        return NULL;
    }
    size_t tlen = end - begin;
    char *str = (char *)malloc(tlen + 1);
    memcpy(str, target_buf + begin, tlen);
    str[tlen] = '\0';
    return str;
}