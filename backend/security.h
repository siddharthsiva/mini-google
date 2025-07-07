#ifndef SECURITY_H
#define SECURITY_H

void sanitize_input(char* str);
void log_security_incident(const char* message, const char* detail);

#endif
