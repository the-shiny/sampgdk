/* Copyright (C) 2012 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "call.h"
#include "log.h"
#include "logprintf.h"

logprintf_t logprintf;

void vlogprintf(const char *format, va_list va) {
	int i;
	int nargs = 1;
	const void **args;

	for (i = 0; format[i] != '\0'; i++) {
		if (format[i] == '%' && format[i + 1] != '%') {
			nargs++;
		}
	}

	if ((args = malloc((nargs + 1) * sizeof(*args))) == NULL) {
		logprintf(strerror(errno));
		return;
	}

	args[0] = format;
	for (i = 1; i <= nargs; i++) {
		args[i] = va_arg(va, const void *);
	}

	call_func_cdecl((void*)logprintf, args, nargs);
	free((void*)args);
}
