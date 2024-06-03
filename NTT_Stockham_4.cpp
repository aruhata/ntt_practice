#include <bits/stdc++.h>
#include <vector>
#include <random>
#include <sys/time.h>

using namespace std;


long primitive_root(long p){
    bool flag = false;
    long g;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(2,p-1);

    while(!flag){
        long k = 1;
        g = dist(gen);
        flag = true;
        for (long i = 1; i <= p-2; i++){
            k = (k * g) % p;
            if(k == 1) flag = false;
        }
    }

    return g;
}

long power_mod(long a, long n, long p){
    if (n == 1) return a;
    else if (n == 0) return 1;
    else if (n % 2 == 0){
        long k = power_mod(a,n/2,p) % p;
        return (k * k) % p;
    }
    else if (n % 2 == 1){
        long k = power_mod(a,(n-1)/2,p) % p;
        return (k * k * a) % p;
    }
    return 0;
}

long power(long a, long n){
    if (n == 1) return a;
    else if (n == 0) return 1;
    else if (n % 2 == 0){
        long k = power(a,n/2);
        return (k * k);
    }
    else if (n % 2 == 1){
        long k = power(a,(n-1)/2);
        return (k * k * a);
    }
    return 0;
}

long inverse(long x, long p){
    return power_mod(x, p-2, p);
}


int main() {
    for (long n = 4; n <= 16; n++){
    double timer = 0.0;
    const long N = power(2,n);
    long p = 65537;

    long ml[p-1];
    long g = 28294;
    ml[0] = 1;
    for (long i = 0; i < p - 2; i++) ml[i + 1] = (ml[i] * g) % p;

    struct timeval start_time, end_time;

    for(long kkk = 0; kkk < 10; kkk++){
            
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0,p);

        long f[N];
        for (long i = 0; i < N; i++) f[i] = dist(gen);
        
        long a, b, c, d;
        long x_copy[N];
        long x[N];
        for (long i = 0; i < N; i++){
            x_copy[i] = f[i];
        }
        long imod2 = 0;
        gettimeofday(&start_time, NULL);
        a = 1;
        b = power(2,n-1);
        for (long i = 0; i < n; i++){
            if (imod2 == 0){
                for (long j = 0; j < b; j++){
                    for (long k = 0; k < a; k++){
                        c = x_copy[a*j+k];
                        d = ml[(k*b * (p-1) / N) % (p-1)] * x_copy[a*j + N/2 + k];
                        x[2*a*j+k] = ((c + d) % p + p) % p;
                        x[2*a*j+k+a] = ((c - d) % p + p) % p;
                    }
                }
            } else {
                for (long j = 0; j < b; j++){
                    for (long k = 0; k < a; k++){
                        c = x[a*j+k];
                        d = ml[(k*b * (p-1) / N) % (p-1)] * x[a*j + N/2 + k];
                        x_copy[2*a*j+k] = ((c + d) % p + p) % p;
                        x_copy[2*a*j+k+a] = ((c - d) % p + p) % p;
                    }
                }
            }
            a = a * 2;
            b = b / 2;
            imod2 = 1 - imod2;
        }

        gettimeofday(&end_time, NULL);
        timer += (end_time.tv_sec - start_time.tv_sec + (end_time.tv_usec - start_time.tv_usec) / 1000000.0) * 100.0;
    }
        std::cout << "(" << n << "," << timer << "),";
    }
}