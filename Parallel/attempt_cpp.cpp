#include<bits/stdc++.h>
#include<omp.h>
#define int long long
#define pb emplace_back
#define mp make_pair
#define tci(v,i) for(auto i=v.begin();i!=v.end();i++)
#define all(v) v.begin(),v.end()
#define rep(i,start,lim) for(long long (i)=(start);i<(lim);i++)
#define revrep(i,n) for(long long i=n-1;i>=0;i--)
#define boost ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define osit ostream_iterator<int> output (cout," ")
#define pv(x) copy(all(x),output)
#define pa(a) rep(i,0,sizeof(a)/sizeof(a[0]))cout<<a[i]<<" "
#define endl '\n'
#define f first
#define s second
#define PI 3.141592653589793
#define set0(x) memset(x,0,sizeof(x))
#define set1(x) memset(x,1,sizeof(x))
#define getarr(arr,n) int arr[n];rep(i,0,n)cin>>a[i]
#define getvec(vec,n) vi vec;int x;rep(i,0,n){cin>>x;vec.pb(x);}
#define sort_uniq(c) (sort(c.begin(), c.end()), c.resize(distance(c.begin(), unique(c.begin(), c.end()))))
#define uniq(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define dg(x) cout<<#x<<':'<<x<<endl;
#define dg2(x,y) cout<<#x<<':'<<x<<' '<<#y<<':'<<y<<endl;
#define dg3(x,y,z) cout<<#x<<':'<<x<<' '<<#y<<':'<<y<<' '<<#z<<':'<<z<<endl;
#define dg4(x,y,z,zz) cout<<#x<<':'<<x<<' '<<#y<<':'<<y<<' '<<#z<<':'<<z<<' '<<#zz<<':'<<zz<<endl;
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
template<typename T> T gcd(T a,T b){if(a==0) return b; return gcd(b%a,a);}
int isPowerof2(int x) { return (x && !(x & x-1)); }

struct Node{
	int id;
	int val;
	int color;
	int l;
	int r;
	Node(){
		id=-1;
		val=-1;
		color=0;
		l=INT_MAX;
		r=INT_MIN;
	}
};

void construct(Node *tree,vi v){
	int n=v.size();
	#pragma omp parallel for
    for(int i=0; i<n; i++) {
        int mi=i+1;
        int D=log2(mi);
        int H=log2(n);
        int J=mi-((int)(1<<D));
        int CI=(2*J+1)*((1<<H)/(1<<D));
        int CL=floor((double)(1.0*CI)/2);
        int Ln=n+1-(1<<H);
        int I=min(CI,CI-CL+Ln);
        tree[mi].id=mi;
        tree[mi].val=v[I-1];
        if(D==H && n!=((1<<(H+1))-1)){
        	tree[mi].color=1;  //red
        }else{
        	tree[mi].color=0;  //black
        }
    }
}

vi search(Node *tree,vi v){
	int m=v.size();
	vi res(m);
	#pragma omp parallel for
	for(int i=0;i<m;i++){
		int key=v[i];
		int cur=1;
		while(tree[cur].id!=-1 && tree[cur].val!=key){
			if(tree[cur].val<key){
				cur=2*cur+1;
			}else{
				cur=2*cur;
			}
		}
		res[i]=cur;
	}
	return res;
}

void insert(Node *tree,vi v){
	int k=v.size();
	vi res=search(tree,v);
	vi external;
	int done[100];
	set0(done);
	#pragma omp parallel for
	for(int i=0;i<k;i++){
		if(done[res[i]]==0 && tree[res[i]].id==-1)external.pb(res[i]);
		tree[res[i]].l=min(tree[res[i]].l,(i+1));
		tree[res[i]].r=max(tree[res[i]].r,(i+1));
		done[res[i]]=1;
	}
	int lim=ceil((double)log2(k));
	for(int times=0;times<lim;times++){

	}
}

int32_t main(){
	Node *tree=new Node[100];

	//Taking imput for construction
	int n;
	cin>>n;
	vi v(n);
	rep(i,0,n){
		cin>>v[i];
	}
	sort(all(v));
	construct(tree,v);

	//Taking input for searching
	int m;
	cin>>m;
	vi keys(m);
	rep(i,0,m){
		cin>>keys[i];
	}
	vi res=search(tree,keys);

	//Taking input for insertion
	int k;
	cin>>k;
	vi ins(k);
	rep(i,0,k){
		cin>>ins[i];
	}
	sort(all(ins));
	//insert(tree,ins);


	//Printing Tree in array form
	for(int i=1;i<=n;i++){
		cout<<tree[i].val<<" ";
	}
	cout<<endl;
	for(int i=1;i<=n;i++){
		cout<<tree[i].color<<" ";
	}
	cout<<endl;

	//Printing result obtained by search function
	for(int i=0;i<res.size();i++){
		cout<<res[i]<<" ";
	}

	return 0;
} 
