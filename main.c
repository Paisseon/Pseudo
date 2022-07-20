#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void root_taurine(void) {
    typedef void (*pseudo_uid_t)(pid_t arg0);
    typedef void (*pseudo_ent_t)(pid_t arg0, uint32_t arg1);
    
    void *handle = dlopen("/usr/lib/libjailbreak.dylib", RTLD_LAZY);
    
    if (handle) {
        dlerror();
        
        pseudo_uid_t setuid_ptr = (pseudo_uid_t)dlsym(handle, "jb_oneshot_fix_setuid_now");
        pseudo_ent_t entitl_ptr = (pseudo_ent_t)dlsym(handle, "jb_oneshot_entitle_now");
        
        setuid_ptr(getpid());
        setuid(0);
        entitl_ptr(getpid(), 2);
    }
    
    const char *err = dlerror();
    
    if (err) {
        printf("%s", err);
        return;
    }
}

int main(int argc, char *argv[]) {
    char cmd[100];
    
    setuid(0);
    setgid(0);
    
    if (getuid()) {
        root_taurine();
        setuid(0);
    }
    
    getuid();
    
    switch (argc) {
        case 1:
            strcpy(cmd, "/bin/bash");
            break;
        case 2:
            strcpy(cmd, argv[1]);
            break;
        default:
            strcpy(cmd, argv[1]);
            
            for (int i = 2; i < argc; i++) {
                strcat(cmd, " ");
                strcat(cmd, argv[i]);
            }
            
            break;
    }
    
    execl("/bin/bash", "/bin/bash", "-c", cmd, NULL);
    
    return 0;
}