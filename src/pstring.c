#include "sit.h"

pstring *
pstring_new(int len) {
  assert(len >= 0);
	pstring *pstr = malloc(sizeof(pstring));
	pstr->val = malloc(len);
	pstr->len = len;
	return pstr;
}

pstring *
pstringf(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char *tmp;
  vasprintf(&tmp, fmt, args);
  pstring *pstr = malloc(sizeof(pstring));
  pstr->val = tmp;
  pstr->len = strlen(tmp);
  return pstr;
}

pstring *
c2pstring(const char *cstr) {
  return pstring_new2(cstr, strlen(cstr));
}

const char *
p2cstring(pstring *pstr) {
  return cstring_new(pstr->val, pstr->len);
}

char * 
pstrnchr(pstring *base, char *start, const char c) {
  if(start<base->val) return NULL;
  int len = base->len - (start - base->val);
  return memchr(start, c, len);
}

char * 
pstrnstr(pstring *base, char *start, const char *c) {
  if(start<base->val) return NULL;
  int len = base->len - (start - base->val);
  int clen = strlen(c);
  return memmem(start, len, c, clen);
}

char *
pstring_cslice(pstring *pstr, long off, int len) {
  char *target = malloc(len + 1);
  memcpy(target, pstr->val + off, len);
  target[len + 1] = '\0';
  return target;
}

void
padd(pstring *pstr, pstring *append) {
  int nlen = pstr->len + append->len;
  char *nbuf = malloc(nlen);
  memcpy(nbuf, pstr->val, pstr->len);
  memcpy(nbuf + pstr->len, append->val, append->len);
  free((void*)pstr->val);
  pstr->val = nbuf;
  pstr->len = nlen;
}

void
paddv(pstring *pstr, const char *fmt, ...) {
       va_list args;
  va_start(args, fmt);
       char *tmp;
       vasprintf(&tmp, fmt, args);
       paddc(pstr, tmp);
       free(tmp);
}

void
paddc(pstring *pstr, const char *cstr) {
  pstring tmp = {
    cstr,
    strlen(cstr)
  };
  padd(pstr, &tmp);
}

void
pstring_copulate(pstring *target, pstring *pstr) {
  target->val = malloc(pstr->len);
  memcpy((void*)target->val, pstr->val, pstr->len);
  target->len = pstr->len;
}

char *
cstring_new(const char *cstr, int len) {
  char *new = malloc(len + 1);
  memcpy(new, cstr, len);
  new[len] = 0;
  return new;
}

pstring *
pcpy(const pstring *pstr) {
  return pstring_new2(pstr->val, pstr->len);
}

long
pstrtol(pstring *pstr) {  
  if(pstr->len > 31) return 0;
  static char buf[32];
  memcpy(buf, pstr->val, pstr->len);
  *(buf + pstr->len) = '\0';
  return strtol(buf, NULL, 10);
}

pstring *
pstring_new2(const char *cstr, int len) {
  pstring *pstr = pstring_new(len);
  memcpy((void *)pstr->val, cstr, len);
  return pstr;
}

pstring *
qc2pstring(const char *cstr) {
  pstring *pstr = pstring_new(strlen(cstr));
  char *val = (char*)pstr->val;
  int len = strlen(cstr);
  for(int i = 1; i < len - 1; i++) {
    if(cstr[i] == '\\') {
      i++;
    } else {
      *val++ = cstr[i];
    }
  }
  pstr->len = val - pstr->val;
  return pstr;
}

void
pstring_free(pstring *pstr) {
	if(pstr != NULL) {
		if(pstr->val != NULL) {
			free((void*) pstr->val);
		}
		free(pstr);
	}
}

int
cpstrcmp(const char *a, pstring *b) {
  pstring ap;
  ap.val = a;
  ap.len = strlen(a);
  return pstrcmp(&ap, b);
}

int
pstrcmp(pstring *a, pstring *b) {
  if(a == b) return 0;
  if(a == NULL) return -1;
  if(b == NULL) return 1;
	int min = a->len > b->len ? b->len : a->len;
	int out = strncmp(a->val, b->val, min);
	if (!out) {
		return a->len - b->len;
	}
	return out;
}

unsigned int
pstrhash(pstring *pstr) {
  return dictGenHashFunction(pstr->val, pstr->len);
}