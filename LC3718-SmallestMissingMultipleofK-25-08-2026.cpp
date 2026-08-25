// LC3718 - Smallest Missing Multiple of K - Daily 25-08-2026

class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
       vector<int> hash(101, 0);

       // Mark the hash if present
       for(int num: nums){
          hash[num]=1;
       }
       
       // Check multiples of k until 100
       int i=1;
       while(k*i<=100){
          if(hash[k*i]==0) break;
          i++;
       }
       return k*i;
    }
};
