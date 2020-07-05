# include "stdio.h"
# define MAX 200
main ( )
{

 int i, j, k, wt, m, p , routes, loop_1, loop_2, time[MAX][MAX]={0},travel_time[MAX][MAX]={0},select_node[MAX], temp, TRUE=1,nr[MAX];

 int hmin[MAX], hmax[MAX], f[MAX], wt_min[MAX], wt_max[MAX],r_nodes[MAX],node_list[MAX][MAX],crit1_satisfied=0;

 int n_routes[MAX], route_tin_max[MAX]={0}, tin_max[MAX]={0}, FALSE =1,max_n_routes = 0, no = 0, number = 0,number_route= 0, max_wt = 0;

 int dep_time[MAX][MAX]={0},arr_time[MAX][MAX]={0},fixed_time[MAX][MAX], min_freq,freq,d_max,d_min, d, num_list[MAX]={0};

 int node_check[MAX]={0},procedure=0,assnd_node=0,assnd_route,check_route [MAX] = {0}, crit1_node [MAX] = {0};

 int max_arr[MAX][MAX]={0}, max_arr_node[MAX]={0},max_arr_crit1=0,count=0,min_tin_max=0, min_arr_node [MAX], plan_hor;

 int count_nodes[MAX]={0},stop_freq[MAX]={0},route_sel,max_count_nodes=0,choose = 0, assnd_node_freq =1, s_freq [MAX] = {0}, sync [MAX]={0}, freq1, freq2, u, v;

 int procedure3;
 printf ("\nEnter total number of routes\n");
 scanf ("%d",&routes);
 printf ("\nEnter total number of nodes in the network\n");
 scanf ("%d",&m);
 for (i=1; i<=routes; i++)
 {
	 printf ("\nEnter the number of nodes on route %d\n", i);
	 scanf ("%d", &r_nodes[i]);
 }
 for (i=1; i<=routes; i++)
 {
	 for (j=1 ;j<=m; j++)
	 {
		 printf ("\nEnter 1if node %d is on route %d, Else enter 0\n", j, i);
		 scanf ("%d", &node_list[i][j]);
		 printf ("\nEnter the travel time on origin of route %d to node %d\n", i, j);
		 scanf ("%d", &travel_time[i][j]);
	 }
 }
 for (i=1; i<=routes; i++)
 {
	 printf ("\nEnter the Min Headway for the route %d\n", i);
	 scanf ("%d", &hmin[i]);
	 printf ("\nEnter the Max Headway for the route %d\n", i);
	 scanf ("%d", &hmax[i]);
	printf ("\nEnter the frequency for the route %d\n", i);
	 scanf ("%d", &f[i]);
 }
 for (i=1; i<=m; i++)
 {
	 printf ("\nEnter the number of routes passing through node %d\n", i);
	 scanf ("%d", &n_routes[i]);
	printf ("\n Enter the minimum allowed waiting time at node %d\n",i);
	 scanf ("%d", &wt_min[i]);
	printf ("\n Enter the maximum allowed waiting time at node %d\n",i);
	 scanf ("%d", &wt_max[i]);
 }
 for (i=1; i<=m; i++)
 {
	 max_wt = wt_max[i];
	 break;
 }
 for (i=1; i<=m; i++)
 {
	 if(wt_max[i]> max_wt)
	 {
	 	
	 }
 }
 printf ("\n Enter the planning horizon(in minutes) during which u want to schedule departure\n");
 scanf ("%d",&plan_hor);
 for ( i=1; i<=routes; i++)
 {
	 if ((plan_hor < ((f[i]-1)*hmin[i])) || (plan_hor > max_wt + (f[i]*hmax[i])))
	 {
		 printf ("\n problem is infeasible due to planning horizon");
		 exit (1);
	 }
 }
 for ( i=1; i<=routes; i++)
 {
	 if (hmin[i]>hmax[i])
	 {
		 printf ("\n Problem is Infeasible as hmin[%d] is greater than hmax[%d]",i,i);
		 exit (1);
	 }
 }
 for ( i=1; i<=routes; i++)
 {
 	stop_freq[i] = 0;
 }
 for ( j=1; j <=m; j++)
 {
	 for (i=1; i<=routes; i++)
	 {
		 if(node_list[i][j] == 1)
		 {
			 tin_max[j] = travel_time[i][j];
			 route_tin_max[j]=i;
			 break;
		 }
	 }
 }
 for ( j=1; j<=m; j++)
 {
	 for (i=1; i<=routes; i++)
	 {
		 if (node_list[i][j] == 1)
		 {
			 if(travel_time[i][j] >= tin_max[j])
			 {
				 tin_max[j] = travel_time[i][j];
				 route_tin_max[j] = i;
			 }
		 }
	 }
 }
 for ( i=1; i<=routes; i++)
 {
	 for (j=1; j<=m; j++)
	 {
		 printf ("\n Arrival time = %d", travel_time[i][j]);
		 printf ("\n Max Travel time = %d", tin_max[j]);
		 printf ("\n Route with Max Travel time = %d", route_tin_max[j]);
	 }
 }
 /* NODE SELECTION PROCEDURE */
 while (assnd_node == 0)
 {
	no = 0;
	number = 0;
	number_route = 0;
	 /* STEP 1 */
	 for ( j=1; j<=m; j++)
	 {
		 if (node_check[j] == 0)
		 {
			 for (i=1; i <= routes; i++)
			 {
				 if (node_list[i][j] == 1)
				 {
					 if (check_route[i] == 1)
					 {
						 max_arr[i][j] = f[i];
						 crit1_node[j] = 1;
					 }
				 }
			 }
		 }
		 max_arr_node[j] = 0;
	 }
	 for (j=1; j<=m; j++)
	 {
		 if ((node_check[j] == 0) && (crit1_node[j] == 1))
		 {
			 for (i=1; i<=routes; i++)
			 {
				 if (node_list[i][j] == 1)
				 {
					 if (max_arr[i][j] > max_arr_node[j])
					 {
						 max_arr_node[j] = max_arr[i][j];
					 }
				 }
			 }
		 }
	 }
	for( j=1; j <= m; j++)
	 {
		 if ((node_check[j] == 0)&&(crit1_node[j] == 1))
		 {
			max_arr_crit1 = max_arr_node[j];
		 	break;
		 }
	 }
	for (j=j+1; j<=m; j++)
	 {
		 if ((node_check[j] == 0) && (crit1_node[j] == 1))
		 {
			 if (max_arr_node[j] >= max_arr_crit1)
			 {
			 	max_arr_crit1 = max_arr_node[j];
			 }
		 }
	 }
	 count = 1;
	 for (j=1; j<=m; j++)
	 {
		 if ((node_check[j] == 0) && (crit1_node[j] == 1))
		 {
			 if (max_arr_node[j] == max_arr_crit1)
			 {
				 if (count == 1)
				 {
					 no = j;
					 crit1_satisfied = 1;
				 }
				 else
				 {
					 no = 0;
					 crit1_satisfied = 0;
				 }
				 

				 count++;
			 }
		 }
	 }
	 if(crit1_satisfied == 1)
	 {
	 	node_check[no] = 1;
	 }
	 if(crit1_satisfied == 0)
	 {
		 /* STEP 2 */
		 for ( j=1; j<=m; j++)
		 {
			 if(node_check[j] == 0)
			 {
				 printf ("\n Crit2, node_check[%d] = %d", j, node_check[j]);
				 max_n_routes = n_routes[j];
				 number_route = j;
				 break;
			 }
		 }
		 for (j=j+1; j<=m; j++)
		 {
			 if (node_check[j] == 0)
			 {
				 if (max_n_routes <= n_routes[j])
				 {
					 max_n_routes = n_routes[j];
					 number_route = j;
				 }
			 }
		 }
		 printf ("\n Max_n_routes = %d", max_n_routes);
		 for (j=1; j<=m; j++)
		 {
			 if (node_check[j]==0)
			 {
				 if (n_routes[j]==max_n_routes)
				 {
					 number = number+1;
					 num_list[j] = 1;
				 }
			 }
		 }
		 if ( number ==1)
		 {
			 no = number_route;
			 node_check[no] = 1;
		 }
		 for ( j=1; j<=m; j++)
		 {
		 	printf ("\n Max Arrival Time for Node %d is %d", j, tin_max[j]);
		 }
		 /* STEP 3 */
		 for (j=1; j<=m; j++)
		 {
			 if ((node_check[j] == 0) && (num_list[j]==1))
			 {
				 min_tin_max = tin_max[j];
				 break;
			 }
		 }
		 for(j=1; j<=m; j++)
		 {
			 if((node_check[j] == 0) && (number!=1))
			 {
				 if (num_list[j]==1)
				 {
					 if((tin_max[j] <= min_tin_max) && (n_routes[j] == max_n_routes))
					 {
					 	no = j;
					 }
				 }
			 }
		 }
		 node_check[no] = 1;
	 }
	 printf ("\n The Node selected is %d", no);
	 for (j=1; j<=m; j++)
	 {
	 	num_list[j]=0;
	 }
	 /* END OF NODE SELECTION */
	 procedure = 0;
	 

	 /* CHECK IF ANY PREVIOUS ROUTE ON SELECTED NODE HAS BEEN
	 ASSIGNED*/
	 for (i=1; i<=routes; i++)
	 {
		 if (node_list[i][no] == 1)
		 {
			 if (check_route[i] == 1)
			 	procedure = 1;
		 }
	 }
     /*PROCEDURE 1*/
	 if (procedure == 0)
	 {
		 for (i=1; i<=routes; i++)
		 {
			 if (node_list[i][no] == 1)
			 {
				 d_min = hmin[i];
				 d_max = hmax[i];
				 break;
			 }
		 }
		 for (i=1; i<=routes; i++)
		 {
			 if(node_list[i][no] == 1)
			 {
				 if(d_min <= hmin[i])
				 	d_min = hmin[i];
				 if(d_max >= hmax[i])
				 	d_max = hmax[i];
				 if(d_max < d_min)
				 	d = 0;
				 else
				 	d = d_min;
			 }
		 }
		 printf("\n Value of d = %d", d);
		 for ( i=1; i<=routes; i++)
		 {
		 	if (node_list[i][no] == 1)
			 {
				 min_freq = f[i];
				 break;
			 }
		 }
		 for (i=1; i<=routes; i++)
		 {
			 if (node_list[i][no] == 1)
			 {
				 if (min_freq >= f[i])
				 {
				 	min_freq = f[i];
				 }
			 }
		 }
		 printf ("\n Minimum freq = %d",min_freq);
		 for (i=1; i<=routes; i++)
		 {
		 if (node_list[i][no] == 1)
		 {
			 if(i == route_tin_max[no] )
			 {
				 arr_time[i][1] = tin_max[no];
				 dep_time[i][1] = (arr_time[i][1] - travel_time[i][no]);
				 stop_freq[i] = 1;
				 check_route[i] = 1;
			 }
			 if(i!= route_tin_max[no])
			 {
				 if (((tin_max[no] - wt_min[no]) >= travel_time[i][no])&&(tin_max[no]-wt_min[no]-travel_time[i][no])>=0)
				 {
					 arr_time[i][1] = (tin_max[no] - wt_min[no]);
					 dep_time[i][1] = (arr_time[i][1] - travel_time[i][no]);
					 stop_freq[i] = 1;
					 check_route[i] = 1;
				 }
				 else
				 {
					 for(wt=wt_min[no];wt<=wt_max[no];wt++)
					 {
						 if((tin_max[no]+wt>=travel_time[i][no])&&((tin_max[no]+wt-travel_time[i][no])<=hmax[i]))
						 {
							 arr_time[i][1] = (tin_max[no]+wt);
							 dep_time[i][1] = (arr_time[i][1] - travel_time[i][no]);
							 stop_freq[i] = 1;
							 check_route[i] = 1;
							 break;
						 }
					 }
				 }
			 }
			 for( freq=2; freq<=min_freq; freq++)
			 {
				 if(d == 0)
				 {
					 stop_freq[i] = freq - 1;
					 break;
					 break;
				 }
				 dep_time[i][freq] = d + dep_time[i][freq-1];
				 arr_time[i][freq] = dep_time[i][freq]+travel_time[i][no];
				 stop_freq[i] = freq;
			 }
		 }
		 }
		 for (i=1; i<=routes; i++)
		 {
			 if (node_list[i][no]==1)
			 {
				 for (freq=1; freq<=stop_freq[i]; freq++)
				 {
					 printf("\n the departure time of %d bus on route %d is= %d\n",freq,i,dep_time[i][freq]);
					 printf("\n the arrivals time of %d bus on route %d at node %dis=%d\n",freq,i,no,arr_time[i][freq]);
				 }
			 }
		 }
	  }  /*END OF PROCEDURE 1 IF LOOP */

		 /* PROCEDURE 2 */
	 else 
	 {
		 assnd_route = 0;
		 printf("\n Starting Middle, check_Route[%d] = %d, assnd_node = %d",1,check_route[1],assnd_node);
		 for (i=1; i<=routes; i++)
		 {
			 if (node_list[i][no] == 1)
			 {
				 if ((check_route[i] == 1) && (stop_freq[i]==f[i]))
				 {
					 assnd_route = i;
					 for (freq=1; freq<=stop_freq[i]; freq++)
					 {
					 	fixed_time[no][freq] = dep_time[i][freq] + travel_time[i][no];
					 }
					 break;
				 }
			 }
			 printf ("\n Exiting Flag Post 1, assnd Route = %d", assnd_route);
		 }
		 printf ("\n The assigned route = %d", assnd_route);
		 for (freq=1;freq<=stop_freq[assnd_route];freq++)
		 {
			 printf ("\n the fixed_time[no][freq]=%d\n", fixed_time[no][freq]);
		 }
		 for (i=1; i<=routes; i++)
		 {
			 if (node_list[i][no] ==1)
			 {
				 if (i!= assnd_route)
				 {
					 for(freq=1;freq<=stop_freq[i];freq++)
					 {
					 	arr_time[i][freq]= dep_time[i][freq]+travel_time[i][no];
					 }
				 }
			 }
		 }
		 loop_1=0;
		 loop_2=0;
		 if(assnd_route != 0)
		 {
			 for( i=1; i<=routes; i++)
			 {
				 if (node_list[i][no] == 1)
				 {
					 if ((i!= assnd_route) && (stop_freq[i]< f[i]))
					 {
						 for (freq=1; freq<=stop_freq[assnd_route]; freq++)
						 {
							 for (wt = wt_min[no]; wt <= wt_max[no]; wt++)
							 {
								 k = stop_freq[i]+1;
								 if ((arr_time[i][k-1]<=(fixed_time[no][freq]- wt))&&((fixed_time[no][freq]- wt-travel_time[i][no])>0))
								 {
									 arr_time[i][k] = (fixed_time[no][freq] - wt);
									 dep_time[i][k] = (arr_time[i][k] - travel_time[i][no]);
									 stop_freq[i] = k;
									 assnd_node_freq = assnd_node_freq + 1;
									 loop_1= 1;
									 if ((k>1)&&((dep_time[i][k] - dep_time[i][k-1]) < hmin[i]))
									 {
										 arr_time[i][k] = 0;
										 dep_time[i][k] = 0;
										 stop_freq[i] = k-1;
										 assnd_node_freq = assnd_node_freq - 1;
										 k=k-1;
										 loop_1 = 0;
										 if(k >= f[i])
										 {
											 break;
											 break;
										 }
									 }
									 break;
								 }
								 if (((fixed_time[no][freq] + wt) >= arr_time[i][k-1])&&((fixed_time[no][freq] + wt-travel_time[i][no])<= (hmax[i]+dep_time[i][k-1])))
								 {
									 arr_time[i][k] = (fixed_time[no][freq] + wt);
									 dep_time[i][k] = (arr_time[i][k] - travel_time[i][no]);
									 stop_freq[i] = k;
									 assnd_node_freq = assnd_node_freq + 1;
									 loop_2 = 1;
									 printf("\n Reached loop2 for wt = %d and freq = %d", wt, freq);
									 if ( (dep_time[i][k] - dep_time[i][k-1]) < hmin[i])
									 {
										 arr_time[i][k] = 0;
										 dep_time[i][k] = 0;
										 stop_freq[i] = k-1;
										 assnd_node_freq = assnd_node_freq - 1;
										 k=k-1;
										 loop_2 = 0;
										 if(k >= f[i])
										 {
											 break;
											 break;
										 }
									 }
								 }
								 if ((loop_1==0)&&(loop_2 == 0))
								 {
								 	k = stop_freq[i];
								 }
								 printf("\n Exiting Flag Post 2");
							 }
							 if (k>= f[i])
							 {
								 break;
								 break;
							 }
						 }
					 }
				 }
				 check_route[i] = 1;
			 }
		 }
		 procedure3 = 0;
		 for ( j=1; j<=m; j++)
		 {
			 for ( i=1; i<=routes; i++)
			 {
				 if (node_list[i][j] == 1)
				 {
					 if (node_check[j] == 0)
					 {
						 procedure3 = 0;
						 break;
					 }
					 

					 else if((node_check[j] == 1) && (stop_freq[i] < f[i]))
					 {
					 	procedure3 = 1;
					 }
				 }
			 }
		 }
	 } /*END OF ELSE LOOP FOR PROCEDURE 2 */
 	   /*PROCEDURE 3 */
	 if (choose == 1)
	 {
		 for ( i=1; i<=routes; i++)
		 {
			 count_nodes[i] = 0;
			 for ( j=1; j<=m; j++)
			 {
				 if((node_list[i][j] == 1) && (dep_time[i][f[i]]==0))
				 {
				 	count_nodes[i] = count_nodes[i] + 1;
				 }
			 }
		 }
		 for ( i=routes; i>=1; i--)
		 {
			 if(dep_time[i][f[i]] == 0)
			 {
				 max_count_nodes = count_nodes[i];
				 route_sel = i;
				 break;
			 }
		 }
		 for( i=routes; i>=1; i--)
		 {
			 if((dep_time[i][f[i]] == 0) && (count_nodes[i]>=max_count_nodes))
			 {
			 	route_sel = i;
			 }
		 }
		 for (freq = (stop_freq[route_sel]+1); freq<=f[route_sel]; freq++)
		 {
			 dep_time[route_sel][freq] = dep_time[route_sel][freq - 1] + hmin[route_sel];
			 stop_freq[route_sel] = freq;
			 break;
		 }
		 for ( i=1; i<=routes; i++)
		 {
			 for (j=1; j<=m; j++)
			 {
				 if ((node_list[i][j] == 1) && (stop_freq[i] < f[i]))
				 {
				 	node_check[j] = 0;
				 }
				 else if(node_list[i][j] == 1)
				 {
				 	node_check[j] = 1;
				 }
			 }
		 }
	 } 
     /* END OF PROCEDURE 3 */
	 for ( j=1; j <=m; j++)
	 {
		 for (i=1; i<=routes; i++)
		 {
			 if (node_list[i][j] == 1)
			 {
				 if ((check_route[i] != 0) && (dep_time[i][f[i]] != 0))
				 {
				 	assnd_node = 1;
				 }
				 else
				 {
					 assnd_node = 0;
					 break;
					 break;
				 }
			 }
		 }
	 }
	 crit1_satisfied = 0;
} /* END OF WHILE LOOP */
/* Loops for printing the Final Results */
for (i=1; i<=routes; i++)
{
	 for ( freq=1; freq<=f[i]; freq++)
	 {
		 printf ("\n Departure Times for Bus %d on route %d = %d", freq, i, dep_time[i][freq]);
		 printf("\n");
	 }
 }
 /* Finding the number of simultaneous arrivals*/
 for( j=1; j<=m; j++)
 {
	 for (i=1; i<=routes-1; i++)
	 {
		 for (p=i+1; p <= routes; p++)
		 {
			 if ((node_list[i][j]==1)&&(node_list[p][j]==1))
			 {
				 for (freq1=1; freq1 <= f[i]; freq1++)
				 {
					 for (freq2=1; freq2 <= f[p]; freq2++)
					 {
						 u = dep_time[i][freq1]+travel_time[i][j];
						 v = dep_time[p][freq2]+travel_time[p][j];
						 if ((abs(u-v) >= wt_min[j]) && (abs(u-v) <= wt_max[j]))
						 {
						 	sync[j] = sync[j] + 1;
						 }
					 }
				 }
			 }
		 }
	 }
 }
 for (j=1; j<=m; j++)
 {
 	printf("\n the number of synchronizations at node %d is = %d\n", j, sync[j]);
 }
}//end of main bracket