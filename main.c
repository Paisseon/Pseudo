#include <dlfcn.h>
#include <stdio.h>
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

int main(int argc, char *argv[], char *envp[]) {
    const char *sh;
    
    setuid(0);
    setgid(0);
    
    if (getuid()) {
        root_taurine();
        setuid(0);
    }
    
    getuid();
    
    if (argc >= 2 && (sh = argv[1], *sh == 47)) {
        ++argv;
    } else {
        sh    = "/bin/bash";
        *argv = "/bin/bash";
    }
    
    execv(sh, (char * const *)argv);
    
    return 0;
}