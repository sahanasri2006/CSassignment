#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <chrono>

using namespace std;

bool is_prime(int n){
    if(n<2) return false;
    if(n==2) return true;
    if(n%2==0) return false;
    for(int i=3;i*i<=n;i+=2)
        if(n%i==0) return false;
    return true;
}

void write_chunk(int start, int end, int fd){
    string buffer="";
    for(int i=start;i<=end;i++){
        if(is_prime(i)) buffer+=to_string(i)+"\n";
        if(buffer.size()>4096){
            write(fd, buffer.c_str(), buffer.size());
            buffer="";
        }
    }
    if(!buffer.empty()) write(fd, buffer.c_str(), buffer.size());
}

int main(int argc, char* argv[]){
    if(argc!=3){
        cout<<"Usage: ./a.out rl rh"<<endl;
        return 1;
    }
    int rl=stoi(argv[1]);
    int rh=stoi(argv[2]);
    int n_cores=sysconf(_SC_NPROCESSORS_ONLN);
    
    auto start_time=chrono::high_resolution_clock::now();
    int fd=open("prime.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
    
    int range=rh-rl+1;
    int chunk=range/n_cores;
    
    for(int i=0;i<n_cores;i++){
        pid_t pid=fork();
        if(pid==0){
            int s=rl+i*chunk;
            int e=(i==n_cores-1)?rh:(s+chunk-1);
            write_chunk(s,e,fd);
            close(fd);
            exit(0);
        }
    }
    
    for(int i=0;i<n_cores;i++) wait(NULL);
    close(fd);
    
    auto end_time=chrono::high_resolution_clock::now();
    chrono::duration<double> diff=end_time-start_time;
    cout<<"AI Solution Time: "<<diff.count()<<"s using "<<n_cores<<" processes."<<endl;
    return 0;
}