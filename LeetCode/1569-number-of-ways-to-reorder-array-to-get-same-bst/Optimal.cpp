#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using ull=unsigned long long;
using vi=vector<int>;
using vll=vector<ll>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

template <typename T>
using minheap=priority_queue<T,vector<T>,greater<T>>;

template <typename T>
using maxheap=priority_queue<T>;

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

template <typename T>
bool chmax(T& a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T>
bool chmin(T& a, const T& b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
class Solution {
private:
    static constexpr ll MOD = 1e9 + 7;

    ll fact[1001];
    ll invFact[1001];

    ll modPow(ll a, ll e) {
        ll res = 1;

        while (e) {
            if (e & 1)
                res = res * a % MOD;

            a = a * a % MOD;
            e >>= 1;
        }

        return res;
    }

    void init() {
        fact[0] = 1;

        for (int i = 1; i <= 1000; i++)
            fact[i] = fact[i - 1] * i % MOD;

        invFact[1000] = modPow(fact[1000], MOD - 2);

        for (int i = 1000; i >= 1; i--)
            invFact[i - 1] = invFact[i] * i % MOD;
    }

    ll nCr(int n, int r) {
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    }
public:
    int numOfWays(vector<int>& nums) {
        int n=nums.size();
        init();
        vector<array<int,2>> adj(n,{-1,-1});
        int root=nums[0]-1;
        auto insert=[&](int x){
            int curr=root;
            while(curr>=0){
                auto &[left,right]=adj[curr];
                if(x<curr){
                    if(left==-1){
                        left=x;
                        return;
                    }
                    else{
                        curr=left;
                    }
                }
                else{
                    if(right==-1){
                        right=x;
                        return;
                    }
                    else curr=right;
                }
            }
        };
        for(int i=1;i<n;i++){
            insert(nums[i]-1);
        }
        auto dfs=[&adj,this](this auto &&self,int root)->pair<ll,ll>{  //ways,size
            if(root==-1) return pair<ll,ll>(1,0);
            auto [lw,ls]=self(adj[root][0]);
            auto [rw,rs]=self(adj[root][1]);
            ll cw=(nCr(ls+rs,rs)*(lw*rw%MOD))%MOD;
            return {cw,ls+rs+1};
        };
        return dfs(nums[0]-1).first-1;
    }
};