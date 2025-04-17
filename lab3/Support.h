#ifndef SUPPORT_H
#define SUPPORT_H
#include <vector>

using namespace std;

class isprime {
  public:
    isprime(bool v=false);
    bool operator()(int);

  private:
    void expand_known_primes(int);

    bool verbose;
    vector<int> known_primes;
};

#endif
