#include <bits/stdc++.h>

void merge_sort(std::vector<std::pair<int,int>>& v)
{
    if(v.size() <= 1)
        return ;
    std::vector<std::pair<int,int>> l,r;
    for(int i = 0;  i < v.size() ; i++)
    {
        if(i < v.size()/2)
            l.push_back(v[i]);
        else
            r.push_back(v[i]);
    }
    merge_sort(l);
    merge_sort(r);
    for(int i = 0 , j = 0 , k = 0; i < l.size() || j < r.size();k++)
    {
        if(j == r.size())
        {
            v[k] = l[i];
            i++;
            continue;
        }
        if(i == l.size())
        {
            v[k] = r[j];
            j++;
            continue;
        }
        if(l[i].first < r[j].first)
        {
            v[k] = l[i];
            i++;
            continue;
        }
        else
        {
            v[k] = r[j];
            j++;
            continue;
        }
    }

} 
std::vector<long long> jb_seq(unsigned long  long n)
{
    std::vector<long long> res = {0,1};
    long long a = 0;
    long long b = 1;
    long long k = a + 2 * b;
    while(k <= n)
    {
        res.push_back(k);
        a = b;
        b = k;
        k = a + 2 * b;
    }
    return (res);
}

int main(int n,char **arr)
{
    std::vector<int> v;
    for(int i = 1 ; i < n ; i++)
    {
        v.push_back(atoi(arr[i]));
    }
    std::vector<std::pair<int,int>> w;
    for(int i = 1 ; i < v.size() ; i += 2)
    {
        w.push_back(std::make_pair(std::max(v[i],v[i-1]),std::min(v[i],v[i-1])));
    }
    merge_sort(w);
    std::vector<long long> final;
    std::vector<long long> lfs;
    for(int i = 0 ; i < w.size() ; i++)
    {
        final.push_back(w[i].first);
        lfs.push_back(w[i].second);
    }
    std::vector<long long> jacob_sequence = jb_seq(lfs.size());
    int prev = -1;
    for(int i = 0 ; i < jacob_sequence.size() ; i++)
    {
        long long next = std::min((long long)lfs.size() - 1,jacob_sequence[i]);
        for(int j = next ; j > prev ; j--)
        {
            std::vector<long long>::iterator it = std::upper_bound(final.begin(), final.begin() + j + cnt,lfs[j]);
            final.insert(it, lfs[j]);
        }
        prev = next;
    }
    for(int i = 0 ; i < final.size() ;i++)
        std::cout<<final[i]<<" ";
    std::cout<<"\n";
}