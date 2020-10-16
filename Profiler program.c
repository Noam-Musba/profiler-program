
#include <sys/ptrace.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/user.h>
#include <errno.h>

#define MAX_CHARS 255
#define MAX_VARS 24

static void swap(char *xp, char *yp){
    char tmp[MAX_CHARS];
    strcpy(tmp, xp);
    strcpy(xp, yp);
    strcpy(yp, tmp);
}

static void bubbleSort(char var[MAX_VARS][MAX_CHARS],char reg[MAX_VARS][MAX_CHARS], int n){
   int i, j;
   bool swapped;
   for (i = 0; i < n-1; i++){
     swapped = false;
     for (j = 0; j < n-i-1; j++){
        if (strcmp(var[j], var[j+1]) > 0){
           swap(var[j], var[j+1]);
           swap(reg[j], reg[j+1]);
           swapped = true;
        }
     }
     // if no two elements were swapped by inner loop, then break
     if (!swapped)
        break;
   }
}

void run_diffmerge_vars(const char var[][MAX_CHARS], const char reg[][MAX_CHARS], int n,
                        const struct user_regs_struct start_regs, const struct user_regs_struct end_regs){
    long long int reg1 = 0;
     long long int reg2 = 0;
     int reg_int1 = 0;
     int reg_int2 = 0;
     short int reg_short1 = 0;
     short int reg_short2 = 0;
     signed char reg_char1 = 0;
     signed char reg_char2 = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(reg[i],"rax") == 0){
            if(start_regs.rax != end_regs.rax){
                printf("PRF:: %s: %lld->%lld\n", var[i], start_regs.rax, end_regs.rax);
            }
            continue;
        }
        if(strcmp(reg[i],"rbx") == 0){
            if(start_regs.rbx != end_regs.rbx){
                printf("PRF:: %s: %lld->%lld\n", var[i], start_regs.rbx, end_regs.rbx);
            }
            continue;
        }
        if(strcmp(reg[i],"rcx") == 0){
            if(start_regs.rcx != end_regs.rcx){
                printf("PRF:: %s: %lld->%lld\n", var[i], start_regs.rcx, end_regs.rcx);
            }
            continue;
        }
        if(strcmp(reg[i],"rdx") == 0){
            if(start_regs.rdx != end_regs.rdx){
                printf("PRF:: %s: %lld->%lld\n", var[i], start_regs.rdx, end_regs.rdx);
            }
            continue;
        }
        if(strcmp(reg[i],"rsi") == 0){
            if(start_regs.rsi != end_regs.rsi){
                printf("PRF:: %s: %lld->%lld\n", var[i], start_regs.rsi, end_regs.rsi);
            }
            continue;
        }
        if(strcmp(reg[i],"eax") == 0){
            reg_int1 = start_regs.rax & 0x00000000FFFFFFFF;
            reg_int2 = end_regs.rax & 0x00000000FFFFFFFF;
            if(reg_int1 != reg_int2){
                printf("PRF:: %s: %d->%d\n", var[i], reg_int1, reg_int2);
            }
            continue;
        }
        if(strcmp(reg[i],"ebx") == 0){
            reg_int1 = start_regs.rbx & 0x00000000FFFFFFFF;
            reg_int2 = end_regs.rbx & 0x00000000FFFFFFFF;
            if(reg_int1 != reg_int2){
                printf("PRF:: %s: %d->%d\n", var[i], reg_int1, reg_int2);
            }
            continue;
        }
        if(strcmp(reg[i],"ecx") == 0){
            reg_int1 = start_regs.rcx & 0x00000000FFFFFFFF;
            reg_int2 = end_regs.rcx & 0x00000000FFFFFFFF;
            if(reg_int1 != reg_int2){
                printf("PRF:: %s: %d->%d\n", var[i], reg_int1, reg_int2);
            }
            continue;
        }
        if(strcmp(reg[i],"edx") == 0){
            reg_int1 = start_regs.rdx & 0x00000000FFFFFFFF;
            reg_int2 = end_regs.rdx & 0x00000000FFFFFFFF;
            if(reg_int1 != reg_int2){
                printf("PRF:: %s: %d->%d\n", var[i], reg_int1, reg_int2);
            }
            continue;
        }
        if(strcmp(reg[i],"esi") == 0){
            reg_int1 = start_regs.rsi & 0x00000000FFFFFFFF;
            reg_int2 = end_regs.rsi & 0x00000000FFFFFFFF;
            if(reg_int1 != reg_int2){
                printf("PRF:: %s: %d->%d\n", var[i], reg_int1, reg_int2);
            }
            continue;
        }
        if(strcmp(reg[i],"ax") == 0){
            reg_short1 = start_regs.rax & 0x000000000000FFFF;
            reg_short2 = end_regs.rax & 0x000000000000FFFF;
            if(reg_short1 != reg_short2){
                printf("PRF:: %s: %hd->%hd\n", var[i], reg_short1, reg_short2);
            }
            continue;
        }
        if(strcmp(reg[i],"bx") == 0){
            reg_short1 = start_regs.rbx & 0x000000000000FFFF;
            reg_short2 = end_regs.rbx & 0x000000000000FFFF;
            if(reg_short1 != reg_short2){
                printf("PRF:: %s: %hd->%hd\n", var[i], reg_short1, reg_short2);
            }
            continue;
        }
        if(strcmp(reg[i],"cx") == 0){
            reg_short1 = start_regs.rcx & 0x000000000000FFFF;
            reg_short2 = end_regs.rcx & 0x000000000000FFFF;
            if(reg_short1 != reg_short2){
                printf("PRF:: %s: %hd->%hd\n", var[i], reg_short1, reg_short2);
            }
            continue;
        }
        if(strcmp(reg[i],"dx") == 0){
            reg_short1 = start_regs.rdx & 0x000000000000FFFF;
            reg2 = end_regs.rdx & 0x000000000000FFFF;
            if(reg_short1 != reg_short2){
                printf("PRF:: %s: %hd->%hd\n", var[i], reg_short1, reg_short2);
            }
            continue;
        }
        if(strcmp(reg[i],"si") == 0){
            reg_short1 = start_regs.rsi & 0x000000000000FFFF;
            reg_short2 = end_regs.rsi & 0x000000000000FFFF;
            if(reg_short1 != reg_short2){
                printf("PRF:: %s: %hd->%hd\n", var[i], reg_short1, reg_short2);
            }
            continue;
        }
        if(strcmp(reg[i],"ah") == 0){
            reg1 = start_regs.rax & 0x000000000000FF00;
            reg2 = end_regs.rax & 0x000000000000FF00;
            reg_char1 = reg1 >> 8;
            reg_char2 = reg2 >> 8;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
        if(strcmp(reg[i],"bh") == 0){
            reg1 = start_regs.rbx & 0x000000000000FF00;
            reg2 = end_regs.rbx & 0x000000000000FF00;
            reg_char1 = reg1 >> 8;
            reg_char2 = reg2 >> 8;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
        if(strcmp(reg[i],"ch") == 0){
            reg1 = start_regs.rcx & 0x000000000000FF00;
            reg2 = end_regs.rcx & 0x000000000000FF00;
            reg_char1 = reg1 >> 8;
            reg_char2 = reg2 >> 8;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
        if(strcmp(reg[i],"dh") == 0){
            reg1 = start_regs.rdx & 0x000000000000FF00;
            reg2 = end_regs.rdx & 0x000000000000FF00;
            reg_char1 = reg1 >> 8;
            reg_char2 = reg2 >> 8;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
        if(strcmp(reg[i],"al") == 0){
            reg_char1 = start_regs.rax & 0x00000000000000FF;
            reg_char2 = end_regs.rax & 0x00000000000000FF;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
        if(strcmp(reg[i],"bl") == 0){
            reg_char1 = start_regs.rbx & 0x00000000000000FF;
            reg_char2 = end_regs.rbx & 0x00000000000000FF;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
        if(strcmp(reg[i],"cl") == 0){
            reg_char1 = start_regs.rcx & 0x00000000000000FF;
            reg_char2 = end_regs.rcx & 0x00000000000000FF;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
        if(strcmp(reg[i],"dl") == 0){
            reg_char1 = start_regs.rdx & 0x00000000000000FF;
            reg_char2 = end_regs.rdx & 0x00000000000000FF;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
        if(strcmp(reg[i],"sil") == 0){
            reg_char1 = start_regs.rsi & 0x00000000000000FF;
            reg_char2 = end_regs.rsi & 0x00000000000000FF;
            if(reg_char1 != reg_char2){
                printf("PRF:: %s: %hhd->%hhd\n", var[i], reg_char1, reg_char2);
            }
            continue;
        }
    }
}

void run_breakpoint_debugger_solution(const pid_t child_pid, const char* start, const char* end,
                    const char var_names[MAX_VARS][MAX_CHARS], const char reg_names[MAX_VARS][MAX_CHARS], int size){
    //setup
    int wait_status = 0;
    struct user_regs_struct start_regs;
    struct user_regs_struct end_regs;
    int ptrace_value = 0;
    //wait for it (to start)
    wait(&wait_status);
    //load the original commands aside
    unsigned long long start_addr = strtol(start,NULL,16);
    unsigned long long end_addr = strtol(end,NULL,16);
    errno = 0;
    long long start_data = ptrace(PTRACE_PEEKTEXT, child_pid, (void*)start_addr, NULL);
    if(errno == EBUSY || errno == EFAULT || errno == EINVAL || errno==EIO || errno == EPERM || errno == ESRCH) {
        exit(1);
    }
    errno = 0;
    long long end_data = ptrace(PTRACE_PEEKTEXT, child_pid, (void*)end_addr, NULL);
    if(errno == EBUSY || errno == EFAULT || errno == EINVAL || errno==EIO || errno == EPERM || errno == ESRCH) {
        exit(1);
    }
    //setting traps
    unsigned long long start_trap = (start_data & 0xFFFFFFFFFFFFFF00) | 0xCC;
    unsigned long long end_trap = (end_data & 0xFFFFFFFFFFFFFF00) | 0xCC;
    //planting traps
    ptrace_value = ptrace(PTRACE_POKETEXT, child_pid, (void*)start_addr, (void*)start_trap);
    if(ptrace_value == -1) exit(1);
    ptrace_value = ptrace(PTRACE_POKETEXT, child_pid, (void*)end_addr, (void*)end_trap);
    if(ptrace_value == -1) exit(1);
    //continue to start trap
    ptrace_value = ptrace(PTRACE_CONT, child_pid, NULL, NULL);
    if(ptrace_value == -1) exit(1);
    //reach the start trap
    wait(&wait_status);
    while(WIFSTOPPED(wait_status)){
        //copy regs before things are going down
        ptrace_value = ptrace(PTRACE_GETREGS, child_pid, 0, &start_regs);
        if(ptrace_value == -1) exit(1);
        //set the original data back instead of the breakpoint
        ptrace_value = ptrace(PTRACE_POKETEXT, child_pid, (void*)start_addr, (void*)start_data);
        if(ptrace_value == -1) exit(1);
        start_regs.rip -=1;
        ptrace_value = ptrace(PTRACE_SETREGS, child_pid, 0, &start_regs);
        if(ptrace_value == -1) exit(1);POKETEXT, child_pid, (void*)end_addr, (void*)end_trap);
        if(ptrace_value == -1) exit(1);
        //let all go down in the code
        ptrace_value = ptrace(PTRACE_CONT, child_pid, 0, 0);
        if(ptrace_value == -1) exit(1);
        //reach the end trap
        wait(&wait_status);
        if (WIFEXITED(wait_status)) break;
        //set the original data back instead of the breakpoint
        ptrace_value = ptrace(PTRACE_POKETEXT, child_pid, (void*)end_addr, (void*)end_data);
        if(ptrace_value == -1) exit(1);
        ptrace_value = ptrace(PTRACE_GETREGS, child_pid, 0, &end_regs);
        if(ptrace_value == -1) exit(1);
        end_regs.rip -=1;
        ptrace_value = ptrace(PTRACE_SETREGS, child_pid, 0, &end_regs);
        if(ptrace_value == -1) exit(1);
        ptrace_value = ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL);
        if(ptrace_value == -1) exit(1);
        wait(&wait_status);
        //copy regs after debugging
        ptrace_value = ptrace(PTRACE_GETREGS, child_pid, 0, &end_regs);
        if(ptrace_value == -1) exit(1);
        //print changes
        run_diffmerge_vars(var_names, reg_names, size, start_regs, end_regs);
        ptrace_value = ptrace(PTRACE_POKETEXT, child_pid, (void*)start_addr, (void*)start_trap);
        if(ptrace_value == -1) exit(1);
        //continue to the next breakpoint
        ptrace_value = ptrace(PTRACE_CONT, child_pid, 0, 0);
        if(ptrace_value == -1) exit(1);
        wait(&wait_status);
        if (WIFEXITED(wait_status)) break;
    }
}

void run_breakpoint_debugger_singelstep(const pid_t child_pid, const char* start,
                    const char var_names[MAX_VARS][MAX_CHARS], const char reg_names[MAX_VARS][MAX_CHARS], int size){
    //setup
    int wait_status = 0;
    struct user_regs_struct start_regs;
    struct user_regs_struct end_regs;
    int ptrace_value = 0;
    //wait for it (to start)
    wait(&wait_status);
    //load the original commands aside
    unsigned long long start_addr = strtol(start,NULL,16);
    errno = 0;
    long long start_data = ptrace(PTRACE_PEEKTEXT, child_pid, (void*)start_addr, NULL);
    if(errno == EBUSY || errno == EFAULT || errno == EINVAL || errno==EIO || errno == EPERM || errno == ESRCH) {
        exit(1);
    }
    //setting traps
    unsigned long long start_trap = (start_data & 0xFFFFFFFFFFFFFF00) | 0xCC;
    //planting traps
    ptrace_value = ptrace(PTRACE_POKETEXT, child_pid, (void*)start_addr, (void*)start_trap);
    if(ptrace_value == -1) exit(1);
    //continue to start trap
    ptrace_value = ptrace(PTRACE_CONT, child_pid, NULL, NULL);
    if(ptrace_value == -1) exit(1);
    //reach the start trap
    wait(&wait_status);
    while(WIFSTOPPED(wait_status)){
        //copy regs
        ptrace_value = ptrace(PTRACE_GETREGS, child_pid, 0, &start_regs);
        if(ptrace_value == -1) exit(1);
        //set the original data back instead of the breakpoint
        ptrace_value = ptrace(PTRACE_POKETEXT, child_pid, (void*)start_addr, (void*)start_data);
        if(ptrace_value == -1) exit(1);
        start_regs.rip -=1;
        ptrace_value = ptrace(PTRACE_SETREGS, child_pid, 0, &start_regs);
        if(ptrace_value == -1) exit(1);
        //reset the trap
        ptrace_value = ptrace(PTRACE_SINGLESTEP, child_pid, NULL, NULL);
        if(ptrace_value == -1) exit(1);
        wait(&wait_status);
        ptrace_value = ptrace(PTRACE_POKETEXT, child_pid, (void*)start_addr, (void*)start_trap);
        if(ptrace_value == -1) exit(1);
        ptrace_value = ptrace(PTRACE_GETREGS, child_pid, 0, &end_regs);
        if(ptrace_value == -1) exit(1);
        //print changes
        run_diffmerge_vars(var_names, reg_names, size, start_regs, end_regs);

        //let program continue
        ptrace_value = ptrace(PTRACE_CONT, child_pid, 0, 0);
        if(ptrace_value == -1) exit(1);
        //reach the end trap
        wait(&wait_status);
        if (WIFEXITED(wait_status)) break;
    }
}

//trace the son and execute him while father debug him
pid_t run_target(const char *program, char *argv_program[]){
    pid_t pid = 0;
    pid = fork();
    if(pid > 0){
        return pid;
    }else if(pid == 0){
        if(ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1){
            exit(1);
        }
        if(execv(program, argv_program) == -1){
		    exit(1);
	    }
    }else{
        exit(1);
    }
}

int main(int argc, char *argv[]){
    pid_t child_pid = 0;
    bool running = true;
    char str1[MAX_CHARS];
    char str2[MAX_CHARS];
    char var_names[MAX_VARS][MAX_CHARS];
    char reg_names[MAX_VARS][MAX_CHARS];
    int i = 0;
    while(running){
        scanf("%s", str1);
        scanf("%s", str2);
        if((strcmp(str1, "run")==0)&&(strcmp(str2, "profile")==0)){
            running = false;
            continue;
        }
        strcpy(var_names[i], str1);
        strcpy(reg_names[i], str2);
        ++i;
    }
    child_pid = run_target(argv[3], (argv + 3));
    bubbleSort(var_names, reg_names, i);
    if(strcmp(argv[1],argv[2])==0){
        run_breakpoint_debugger_singelstep(child_pid, argv[1], var_names, reg_names, i);
        return 0;
    }
    run_breakpoint_debugger_solution(child_pid, argv[1], argv[2], var_names, reg_names, i);
    return 0;
}
