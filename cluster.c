#include <stdio.h>
#include <stdlib.h>

int main(void){

  int G[1000][1000];  //隣接行列
  int R[1000][1000];  //隣接している頂点番号を記録
  int N[1000] = {0};  //隣接している頂点数を記録
  int C[1000] = {0};  //クラスター数を記録
  double cluster = 0;
  int last_node_number = 0;
  int a,b;
  int i,j,k;
  char fname[128];

  FILE *fp;

        printf("Input filename(c_elegans.txt or dolphins_1994_2001.txt or karate_club.txt): ");
	scanf("%s",fname);
	
	fp = fopen(fname, "r");

	if (fp == NULL) {
		printf("file open error\n");
		return -1;
	}


	printf("読み込みの確認\n");
	while (fscanf(fp, "%d %d", &a, &b) != EOF) { // \n不要?
		G[a][b] = 1;
		G[b][a] = 1;
	       
		
		printf("%d,%d\n",a,b);

		if (last_node_number < a) { last_node_number = a; }
		if (last_node_number < b) { last_node_number = b; }

	}
	printf("\n");

	fclose(fp);

	printf("隣接行列\n");
        for (i=0;i<=last_node_number;i++){  //隣接行列表示
	  for (j=0;j<=last_node_number;j++){ 
	    printf("%d ",G[i][j]);
	  }
	  printf("\n");
        }
	printf("\n");


	//隣接している頂点数を計算
	for (i=0;i<=last_node_number;i++){
	  for (j=0;j<=last_node_number;j++){
	    if ( G[i][j] == 1 ){N[i] ++;}
	  }
	}

	//クラスターの判別
	//step1.各頂点に隣接している頂点数を抜き出す
	k=0;
	for(i=0;i<=last_node_number;i++){
	  for(j=0;j<=last_node_number;j++){
	    if( G[i][j] == 1 ){R[i][k] = j; k++;}
	  }
	  R[i][k] = -1;  //tailを示すため
	  k=0;
	}

	//step2.抜き出された頂点同士が隣接しているか調べる

	for(i=0;i<=last_node_number;i++){
	  j=0;
	  while(R[i][j] != -1){
	    k = j + 1;
	    while(R[i][k] != -1){
	      if ( G[ R[i][j] ][ R[i][k] ] == 1 ){C[i] = C[i] + 1;} //抜き出された隣接した頂点同士にも繋がりがあればクラスター
	      k++;
	    }
	  j++;
	  }
	}

	j=0;
	for(i=0;i<=last_node_number;i++){
	  printf("%d -> ",i);
	  j = 0;
	  while(R[i][j] != -1){
	    printf("%d ",R[i][j]);
	    j++;
	  }
	  printf("\n");
	}

	for(i=0;i<=last_node_number;i++){
	  if(N[i] <= 1){cluster += 0;}
	  else         {cluster += (double)C[i] * 2 / (N[i] * (N[i] - 1));}
	  printf("N_%d = %d, cluster数 = %d\n",i,N[i],C[i]);
	  if(N[i] <= 1){printf("C_%d = 0\n",i);}
	  else         {printf("C_%d = %f\n",i, (double)C[i] *2 /(N[i] * (N[i] -1)));}
	}

	printf("\n");
	cluster = cluster / (last_node_number + 1);  //ノード番号が０からであることに注意
	printf("Cluster coefficient  C = %f\n\n",cluster);

	return 0;
}
	
