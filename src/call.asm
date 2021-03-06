; Copyright (C) 2012 Zeex
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.

global get_ret_addr
global call_func_cdecl
global call_func_stdcall

section .text

get_ret_addr:
	mov eax, dword [esp + 4]
	cmp eax, 0
	jnz .init
	mov eax, ebp
.init:
	mov ecx, dword [esp + 8]
	mov edx, 0
.loop:
	cmp ecx, 0
	jl .exit
	mov edx, dword [eax + 4]
	mov eax, dword [eax]
	dec ecx
	jmp .loop
.exit:
	mov eax, edx
	ret

call_func_cdecl:
	mov eax, dword [esp + 4]
	mov edx, dword [esp + 8]
	mov ecx, dword [esp + 12]
	push edi
	mov edi, ecx
	sal edi, 2
	push esi
.loop:
	cmp ecx, 0
	jle .call
	dec ecx
	mov esi, dword [edx + ecx * 4]
	push esi
	jmp .loop
.call:
	call eax
	add esp, edi
	pop esi
	pop edi
	ret

call_func_stdcall:
	mov eax, dword [esp + 4]
	mov edx, dword [esp + 8]
	mov ecx, dword [esp + 12]
	push esi
.loop:
	cmp ecx, 0
	jle .call
	dec ecx
	mov esi, dword [edx + ecx * 4]
	push esi
	jmp .loop
.call:
	call eax
	pop esi
	ret
