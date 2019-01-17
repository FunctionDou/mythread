// void switch_to(int current_thread)

// 本质是改变esp
.section .text
.global switch_to

switch_to:
  push %ebp
  // 更改栈帧，用于寻参
  mov %esp, %ebp 

  // 保存现场 
  push %edi
  push %esi
  push %eax
  push %ebx
  push %ecx
  push %edx

  pushfl
 
  // 切换栈 
  // 保存当前 esp
  mov current, %eax 
  mov %esp, 8(%eax)
  // 取下一个线程 id
  mov 8(%ebp), %eax 
  // 将 current_thread 重置为下一个线程
  mov %eax, current
  // 切换到下一个线程的栈 
  mov 8(%eax), %esp

  // 恢复现场 
  popfl
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax
	popl %esi
	popl %edi

	popl %ebp
  ret


