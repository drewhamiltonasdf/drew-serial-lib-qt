#ifndef DREW_UTIL_H
#define DREW_UTIL_H

#include <QString>

static void removeLeadingzeros(QString &s){ int i = 0; while(i < s.length() && s[i]=='0'){  i++; } s.remove(0,i); }

#endif // DREW_UTIL_H
