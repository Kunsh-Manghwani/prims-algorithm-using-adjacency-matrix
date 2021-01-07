#include<stdio.h>
#define max 10
#define temp 0
#define perm 1
#define true 1
#define False 0
#define inf 9999

struct node{
	int predecessor;
	int dist;
	int status;
};

struct edge{
	int u;
	int v;
};

int adj[max][max];
int n;

void create_graph(){
	int i,max_edges,origin,destin,wt;
	printf("Enter number of vertices: ");
	scanf("%d",&n);
	max_edges= n*(n-1)/2;
	for(i=1;i<=max_edges;i++){
		printf("Enter Edges %d :(0 0 to quit): ",i);
		scanf("%d",&origin);
		scanf("%d",&destin);
		fflush(stdin);
		if((origin==0)&&(destin==0)){
			break;
		}/* further change to continue*/
		printf("Enter edge weight:- ");
		scanf("%d",&wt);
		if(origin>n||destin>n||origin<=0||destin<=0){
			printf("Invalid Edge");
			i--;
		}else{
			adj[origin][destin]=wt;
			adj[destin][origin]=wt;
		}
	}
	if(i<n-1){
		printf("spanning tree not possible");
	}
}

void display(){
	int i,j;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			printf("%3d",adj[i][j]);
		}
		printf("\n");
	}
}

int maketree(struct edge tree[max],int *weight){
	struct node state[max];
	int i,k,min,count,current,newdist,m,u1,v1;
	*weight =0;
	for(i=1;i<=n;i++){
		state[i].predecessor =0;
		state[i].dist=inf;
		state[i].status=temp;
	}
	state[1].predecessor=0;
	state[1].dist=0;
	state[1].status=perm;
	
	current=1;
	count=0;
	
	while(all_perm(state)!=true){
		for(i=1;i<=n;i++){
			if((adj[current][i] >0)&& (state[i].status==temp)){
				if(adj[current][i]<state[i].dist){
					state[i].predecessor =current;
					state[i].dist =adj[current][i];
				}
			}
		}
		min = inf;
		for(i=1;i<=n;i++){
			if(state[i].status == temp && state[i].dist<min){
				min = state[i].dist;
				current=i;
			}
		}
		state[current].status=perm;
		u1=state[current].predecessor;
		v1=current;
		count++;
		tree[count].u=u1;
		tree[count].v=v1;
		*weight = *weight + adj[u1][v1];
	}
	return count;
}

int all_perm(struct node state[max]){
	int i;
	for(i=1;i<=n;i++){
		if(state[i].status == temp){
			return False;
		}
	}
	return true;
}

int main(){
	int i,j;
	int path[max];
	int wt_tree,count;
	struct edge tree[max];
	
	create_graph();
	printf("Adjacency matrix is :-\n");
	display();
	
	count = maketree(tree,&wt_tree);
	printf("Weight of spanning tree is : %d\n",wt_tree);
	printf("Edges to be included in spanning tree:\n");
	
	for(i=1;i<=count;i++){
		printf("%d->%d\n",tree[i].u,tree[i].v);
	}	
	return 0;
}
