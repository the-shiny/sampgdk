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

#include <sampgdk/bool.h>
#include <sampgdk/export.h>

#include <sampgdk/a_objects.h>

#include "amx-stack.h"
#include "callback.h"
#include "fakeamx.h"
#include "likely.h"
#include "native.h"

#define register_callbacks register_callbacks__a_objects

#include "a_objects-impl.c"
