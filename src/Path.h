/*
*
* Team ID			:			3149
* Author List		:		Samiksha Patil, Kanhaiya Gawade, Trisha Mehar, Ashish Shevale
* File Name			:		Path.h
* Theme				:		Construct - O - Bot
* Functions			:		int get_distance( int house_no, int warehouse_no ), void find_shortest_path( void ), 
*							void find_shortest_path_with_H5( void ),
*							void house_to_warehouse(int house_no, int warehouse_no, int mode),
*							void warehouse_to_house(int warehouse_no, int house_no, int mode),
							void task5( void )
* Global Variables :		node_of_path node[10]
*
*/

#include "Predef.h"

#define INFT 255 // DEFINE MAXIMUM DIST AS 25

struct node_of_path // STRUCTURE TO STORE FINAL OPTIMUM PATH TO BE FOLLOWED BY THE BOT
{
	int warehouse; // STORE THE WAREHOUSE FROM WHICH THE CM IS TO BE PICKED
	int house; // STORE THE HOUSE TO WHICH THW PICKED CM IS TO BE DELIVERIED
}node[10]; // AS MAX 2 CM ARE TO BE DELIVERIED TO EACH HOUSE THE MAX NODES IN THE PATH ARE 10 ( 2*5 )


/*
* Function Name ::  int get_distance( int house_no, int warehouse_no )
* Input  :: house_no -> number of house whose distance is to be found ( 0 :: H1, 1 :: H2, 2 :: H3, 3 :: H4, 4 :: H5 )
*			warehouse_no -> number of warehouse whose distance is to be found ( 0 :: RED, 1 :: BLACK, 2 :: PINK, 3 :: BROWN, 4 :: GREEN, 5 :: BLUE )
* Output :: int -> distance between the house and warehouse
* Logic  :: returns the predefinedvalue of approximate distance between given house and warehouse
* Example Call  :: get_distance( 0, 2 );
*/
int get_distance(int house_no, int warehouse_no)
{
	switch(house_no)
	{
		case 0: switch(warehouse_no)
		{
			case 0: return  9; // DISTANCE BETWEEN H1 AND RED
			case 1: return  9; // DISTANCE BETWEEN H1 AND BLACK
			case 2: return 11; // DISTANCE BETWEEN H1 AND PINK
			case 3: return  1; // DISTANCE BETWEEN H1 AND BROWN
			case 4: return  1; // DISTANCE BETWEEN H1 AND GREEN
			case 5: return  3; // DISTANCE BETWEEN H1 AND BLUE
			default: return INFT; // DISTANCE BETWEEN H1 AND START
		}
		
		case 1: switch(warehouse_no)
		{
			case 0: return  1; // DISTANCE BETWEEN H2 AND RED
			case 1: return  1; // DISTANCE BETWEEN H2 AND BLACK
			case 2: return  3; // DISTANCE BETWEEN H2 AND PINK
			case 3: return  9; // DISTANCE BETWEEN H2 AND BROWN
			case 4: return  9; // DISTANCE BETWEEN H2 AND GREEN
			case 5: return 11; // DISTANCE BETWEEN H2 AND BLUE
			default: return INFT; // DISTANCE BETWEEN H2 AND START
		}
		
		case 2: switch(warehouse_no)
		{
			case 0: return 11; // DISTANCE BETWEEN H3 AND RED
			case 1: return  9; // DISTANCE BETWEEN H3 AND BLACK
			case 2: return  9; // DISTANCE BETWEEN H3 AND PINK
			case 3: return  3; // DISTANCE BETWEEN H3 AND BROWN
			case 4: return  1; // DISTANCE BETWEEN H3 AND GREEN
			case 5: return  1; // DISTANCE BETWEEN H3 AND BLUE
			default: return INFT; // DISTANCE BETWEEN H3 AND START
		}
		
		case 3: switch(warehouse_no)
		{
			case 0: return  3; // DISTANCE BETWEEN H4 AND RED
			case 1: return  1; // DISTANCE BETWEEN H4 AND BLACK
			case 2: return  1; // DISTANCE BETWEEN H4 AND PINK
			case 3: return 11; // DISTANCE BETWEEN H4 AND BROWN
			case 4: return  9; // DISTANCE BETWEEN H4 AND GREEN
			case 5: return  9; // DISTANCE BETWEEN H4 AND BLUE
			default: return INFT; // DISTANCE BETWEEN H4 AND START
		}
		
		case 4: switch(warehouse_no)
		{
			case 0: return  9; // DISTANCE BETWEEN H5 AND RED
			case 1: return  7; // DISTANCE BETWEEN H5 AND BLACK
			case 2: return  5; // DISTANCE BETWEEN H5 AND PINK
			case 3: return  9; // DISTANCE BETWEEN H5 AND BROWN
			case 4: return  7; // DISTANCE BETWEEN H5 AND GREEN
			case 5: return  5; // DISTANCE BETWEEN H5 AND BLUE
			default: return INFT; // DISTANCE BETWEEN H5 AND START
		}
		default: switch(warehouse_no)
		{
			case 0: return  5; // DISTANCE BETWEEN START AND RED
			case 1: return  7; // DISTANCE BETWEEN START AND BLACK
			case 2: return  9; // DISTANCE BETWEEN START AND PINK
			case 3: return  5; // DISTANCE BETWEEN START AND BROWN
			case 4: return  7; // DISTANCE BETWEEN START AND GREEN
			case 5: return  9; // DISTANCE BETWEEN START AND BLUE
			default: return INFT; // DISTANCE BETWEEN START AND START
		}
	}
}

/*
* Function Name ::  void find_shortest_path( void )
* Input  :: void
* Output :: void
* Logic  :: analyse all combinations of deliveries to be made and find the one with the shortest distance
* Example Call  :: find_shortest_path();
*/
void find_shortest_path()
{
	// CALCULATE THE NUMBER OF DELIVERIES TO BE MADE
	int n = requirement[0]+requirement[1]+requirement[2]+requirement[3]+requirement[4] + 1;
	
	// CREATE A STRUCTURE FOR HOLDING THE GRAPH OF HOUSE AND WAREHOUSES TO VISIT
	struct node
	{
		int house_no;
		int warehouse_no;
		int distance;
	}graph[n]; // CREATE N INSTANCES OF THE GRAPH
	
	int i,j,k; // VARIABLES TO BE USED IN FOR LOOPS
	
	// INITIALIZE THE GRAPH BY INPUTTING THE VALUE OF THE STARTING NODE
	graph[0].house_no = -1;
	graph[0].warehouse_no = -1;
	graph[0].distance = 0;
	
	// FILL IN ALL THE NODES OF THE GRAPH
	k = 1;
	for(i = 0;i < 10;++i) // REPEAT THE FOLLOWING FOR THE WHOLE REQUIREMENTS ARRAY
	{
		if(material[i] != -1) // IF A DELIVERY EXISTS IN THE REQUIREMENT ARRAY, THEN
		{
			graph[k].house_no = i/2; // ENTER THE HOUSE NUMBER AS INDEX OF THE ARRAY
			graph[k].warehouse_no = material[i]; // ENTER THE WAREHOUSE NUMBER AS THE VALUE STORED AT THAT LOCATION
			graph[k].distance = get_distance(i/2, material[i]); // CALCULATE AND STORE THE DISTANCE BETWEEN THE HOUSE AND WAREHOUSE
			++k;
			
		}
	}
	
	// COMPUTE THE WEIGHT MATHRIX FOR THE ABOVE GRAPH
	int weight[n][n]; // 2D ARRAY FOR HOLDING WEIGHTS
	
	for(i = 0;i < n;++i) // REPEAT THE FOLLOWING FOR ALL THE DELIVERIES
	{
		// VARIABLE i COUNTS THE STARTING LOCATION, VARIABLE j CLACULATES THE FINAL DESTINATION
		for(j = 0;j < n;++j)
		{
			if( (i == j) || (j == 0) ) // AS WE NEVER VISIT THE SAME NODE FROM ITSELF, MARK THIS DISTANCE AS INFINITY. WE ALSO NEVER VISIT THE STARTING NODE FROM ANY OTHER NODE
			{
				weight[i][j] = INFT;
			}
			else
			{
				// WEIGHT OF GRAPH = DISTANCE BETWEEN CURRENT HOUSE AND NEXT WARE HOUSE + DISTANCE BETWEEN CURRENT HOUSE AND WAREHOUSE
				weight[i][j] = get_distance(graph[i].house_no, graph[j].warehouse_no) + graph[j].distance; // IF THE FINAL NODE IS VALID, CALCULATE THE WEIGHT
			}
			
		}
	}
	// START CALCULATING PATH FROM THE WEIGHT MATRIX
	
	struct path // STRUCTURE FOR HOLDING THE PATH TO BE TRAVERSED
	{
		int branch; // NUMBER OF BRANCH OF GRAPH TO VISIT
		int branches_left; // NUMBER OF BRANCHES LEFT TO BE ANALYSED
		int distance; // DISTANCE UNTIL NOW
	};
	
	struct path path[n]; // CREATE N INSTANCES OF PATH ONE FOR EACH NODE
	
	int final_path[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; // ARRAY FOR STORING FINAL PATH AFTER ALL THE POSSIBILITIES HAVE BEEN ANALYSED
	int visited[n]; // ARRAY FOR STORING WHTHER A NODE HAS BEEN VISITED
	int min; // VARIABLE FOR STORING THE MINIMUM DISTANCE BETWEEN ALL CHOICES OF NODES TO VISIT
	int branches_to_visit = 0; // TOTAL NUMBR OF BRANCH POSSIBILITIES LEFT TO BE ANALYSED
	int tot_dist1 = 0; // TOTAL DISTANCE OF PATH UPTO NOW
	int tot_dist2; // TOTAL DISTANCE UPTO NOW ( USED WHEN ANALYSING ALL OTHER POSSIBILITIES
	int temp; // VARIABLE FOR HOLDING TEMPORARY DATA
	
	for(i = 0;i < n;++i)
	{
		visited[i] = 0; // MARK ALL NODES AS NOT VISITED
	}
	
	i = 0;
	
	for(k = 0;k < n-1;++k) // SCAN THE ADJACENCY MATRIX AND 
	{
		min = 100; // SET THE DEFAULT MINIMUM DISTANCE AS 100
		for(j = 1;j < n;++j) // REPEAT THE FOLLOWING FOR ALL NODES OF THE GIVEN TASK
		{
			if(i == j) // IF THE ELEMENT BEING ANALYSED IS ON THE MAJOR DISGONAL, THEN SKIP IT AS WE NEVER VISIT FROM ONE NODE TO ITSELF
				continue;
			else if(visited[j] == 0) // IF THAT NODE HASNT BEEN VISITEC YET, THEN
			{
				if(min == weight[i][j]) // IF WIGHT OF CURRENT NODE IS EQUAL TO THE MINIMUM WEIGHT, THEN ANOTHER POSSIBLE PATH IS POSSIBLE
				{
					++path[k].branches_left; // INCREMENTED THE BRANCHES LEFT FOR POSSIBILITY CALCULATION
					path[k].branch = j; // STORE THIS BRANCH IN THE PATH STRUCTURE
				}
				else if(min > weight[i][j]) // IF THE WEIGHT OF CURRENT NODE IS LESS THAN THE MINIMUM WEIGHT
				{
					min = weight[i][j]; // UPDATE THE MINIMUM WEIGHT
					path[k].branch = j; // ADD THIS BRANCH IN THE PATH
					path[k].branches_left = 0; // RESET THE NUMBER OF BRANCHES LEFT
				}
			}
		}
		
		i = path[k].branch; // SET THE CURRENT LOCATION FOR NEXT CALCULATIONS
		visited[i] = 1; // MARK THE CURRENT NODE AS VISITED
		branches_to_visit =branches_to_visit + path[k].branches_left; // UPDATE THE TOTAL NUMBER OF BRANCHES LEFT TO VISITING
		path[k].distance = min; // SET THE DISTANCE IN THE PATH
		tot_dist1 = tot_dist1 + min; // UPDATE THE TOTAL DISTANCE OF PATH UPTO NOW
	}
	
	for(k = 0;k < n-1;++k)
	{
		final_path[k] = path[k].branch; // COPY THE PATH CALCULATED UPTO NOW IN ANOTHER ARRAY SO THAT IT CAN BE COMPARED WITH ANY OTHER NEW PATHS
	}
	
	tot_dist2 = tot_dist1; // COPY THE TOTAL DISTANCE OF CURRENT PATH IN ANOTHER VARIABLE
	
	while(branches_to_visit > 0) // REPEAT THE FOLLOWING UNTIL ALL THE POSSIBILITIES HAVE BEEN ANALYSED
	{
		k = n - 2; // INITIALIZE THE VARIABLE K TO THE LAST ELEMENT OF ARRAY IN WHICH THE PATH CLACULATED UPTO NOW HAS BEEN STORED
		while(path[k].branches_left == 0 && k > 0) // REPEAT UPTO THAT NODE WHICH STILL HAS MORE POSSIBILITIES TO BE EXPLORED, OR UNTIL NO MORE ELEMENTS ARE LEFT
		{
			visited[path[k].branch] = 0; // MARK THESE NODES AS UNVISITED
			tot_dist1  = tot_dist1 - path[k].distance; // SUBTRACT THEIR DISTANCES FROM THE TOTAL DISTANCE VARIABLE
			--k;
		}
		--branches_to_visit; // DECREMENT THE BRANCHES TO VISIT
		visited[path[k].branch] = 0; // MARK THE BRANCH AS UNVISITED
		temp = path[k].branches_left-1; // STORE HOW MANY POSSIBILITIES ARE STILL LEFT TO BE ANALYSED
		--path[k].branches_left; // DECREMENT THE BRANCHES LEFT
		i = path[k-1].branch; // SET THE VARIABLE I AS THE CURRENT NODE
		for(j = 1;j < n && temp >= 0;++j) // REPEAT THE FOLLOWING UNTIL ALL THE POSSIBILITIES HAVE BEEN ANALYSED
		{
			if(i == j) // THE THE ELEMENT IS ON THE MAJOR DISGONAL, THEN SKIP AS WE NEVER A NODE FROM ITSELF
				continue;
			else if(weight[i][j] == path[k].distance && visited[j] == 0) // DECREMENT J UNTIL THE FIRST ELEMENT WITH THE LEAST WEIGHT IS FOUND
			{
				--temp;
			}
		}
		path[k].branch = j-1; // STORE THE CURRENT BRANCH IN THE PATH
		i = j-1; // STORE THE NEXT STARTING LOCATION IN VARIABLE I
		visited[i] = 1; // MARK THE CURRENT NODE AS VISITED
		++k;
		for(;k < n-1;++k) // REPEAT THE FOLLOWING UNTIL ALL THE REMAINING NODES HAVE BEEN ADDDED TO THE PATH
		{
			min = 100; // ASSUME THE MINIMUM DISTANCE
			for(j = 1;j < n;++j) // COMPARE WITH THE REMAINING NODES 
			{
				if(i == j) // IF IT IS A DIAGONAL ELEMENT, THEN SKIP AS WE NEVER VISITTHE SAME NODE FROM ITSELF
					continue;
				else if(visited[j] == 0)
				{
					if(min == weight[i][j]) // IF A NODE WITH THE SAME WEIGHT AS THIS IS FOUND, THEN INCREMENT THE NUMBER OF BRANCHES TO VISIT
					{
						++path[k].branches_left;
						path[k].branch = j;
					}
					else if(min > weight[i][j]) // IF A NODE WITH A SMALLER WEIGHT IS FOUND, THEN THIS IS THE NODE WE MUST VISIT
					{
						min = weight[i][j]; // STORE ITS MINIMUM WEIGHT FOR FUTURE USE
						path[k].branch = j; // STORE THE BRANCH NAME
						path[k].branches_left = 0; // MAKE THE BRANCHES LEFT AS ZERO
					}
				}
			}
			i = path[k].branch; // STORE THE CURRENTLY VISITED BRANCH IN THE VARIABLE I
			visited[i] = 1; // MARK THE BRANCH AS VISITED
			branches_to_visit =branches_to_visit + path[k].branches_left; // INCREMENT THE NUMBER OF BRANCHES YET LEFT TO BE VISITED
			path[k].distance = min; // STORE THE DISTANCE OF THE CURRENT NODE
			tot_dist1 = tot_dist1 + min; // UPDATE THE TOTAL DISTANCE OF PATH UPTO NOW
		}
		for(k = 0;k < n-1;++k)
		{
			final_path[k] = path[k].branch;
		}
		tot_dist2 = tot_dist1;
		if(tot_dist2 > tot_dist1) // IF THE CURRENTLY ANALYSED POSSIBILITY HAS SHORTER PATH THEN THE PREVIOUS ONE, THEN REPLACE THE PREVIOUS POSSIBILITY BY THE CURRENT ONE
		{
			for(k = 0;k < n-1;++k) // COPY THE CURRENT ELEMENTS OF THE PATH INTO THE FINAL_PATH VARIABLE
			{
				final_path[k] = path[k].branch;
			}
			tot_dist2 = tot_dist1; // UPDATE THE TOTAL DISTANCE OF THE CURRENT NEW PATH
		}
	}
	
	for(k = 0;k < n-1;++k) // COPY THE CALCULATED PATH INTO THE FINAL PATH ARRAY
	{
		final_path[k] = path[k].branch;
	}
	
	for(k = 0;k < n-1;++k) // CONVERT THE NODES INTO NAMES OF HOUSES AND WAREHOUSES
	{
		node[k].warehouse = graph[final_path[k]].warehouse_no;
		node[k].house = graph[final_path[k]].house_no;
	}
	
	for(;k < 10;++k) // MARK THE REMAINING NODES AS EMPTY
	{
		node[k].warehouse = -1;
		node[k].house = -1;
	}
}


/*
* Function Name ::  void H5_path( void )
* Input  :: void
* Output :: void
* Logic  :: adds the path to be followed by the bot if it has to cover the house H5 deliveries first
* Example Call  :: H5_path();
*/
void H5_path( void )
{
	int n = requirement[0]+requirement[1]+requirement[2]+requirement[3] + 1; // GET THE NUMBER OF ELEMENTS CURRENTLY IN THE PATH
	if( requirement[4] == 1) // IF H5 REQUIRES ONLY 1 CM, THEN
	{
		for(int i = n-1;i >= 0;--i) // SHIFT THE ELEMENTS OF THE PATH ONE POSITION DOWN
		{
			node[i+1] = node[i];
		}
		
		node[0].warehouse = material[8]; // PUT THE REQUIREMENT OF H5 AT FIRST LOCATION
		node[0].house = 4; // MARK THE FIRST WAREHOUSE TO VISIT AS H5
	}
	
	if( requirement[4] == 2 ) // IF H5 REQUIRES 2 DELIVERIES
	{
		for(int i = n-2;i >= 0;--i) // MAVE THE CURRENT ELEMENTS OF THE PATH ONE POSITION DOWN
		{
			node[i+2].warehouse = node[i].warehouse;
			node[i+2].house = node[i].house;
		}
		int dist1,dist2; // VARIABLES FOR HOLDING DISTANCE BETWEEN FIRST WAREHOUSE OF H5 AND H5, AND SECOND WAREHOUSE OF H5 AND H5
		
		dist1 = get_distance(-1, material[8]) +get_distance(4, material[8]) +2*get_distance(4, material[9]); // DISTANCE FROM START TO WAREHOUSE TO H5
		
		dist2 = get_distance(-1, material[9]) +get_distance(4, material[9]) +2*get_distance(4, material[8]); // DISTANCE FROM START TO WAREHOUSE TO H5
		
		if( dist1 < dist2 ) // IF THE FIRST WAREHOUSE IS CLOSER
		{
			node[0].warehouse = material[8]; // VISIT THE FIRST WAREHOUSE FIRST
			node[0].house = 4;
			node[1].warehouse = material[9]; // NEXT VISIT THE SECOND WAREHOUSE
			node[1].house = 4;
		}
		else // IF THE SECOND WAREHOUSE IS CLOSER
		{
			node[0].warehouse = material[9]; // VISIT THE SECOND WAREHOUSE FIRST
			node[0].house = 4;
			node[1].warehouse = material[8]; // NEXT VISIT THE FIRST WAREHOUSE
			node[1].house = 4;
		}
	}
}

/*
* Function Name ::  void find_shortest_path_with_H5( void )
* Input  :: void
* Output :: void
* Logic  :: calculates the shortest path to be followed by the bot by making the first deliveries to house H5
* Example Call  :: find_shortest_path_with_H5();
*/
void find_shortest_path_with_H5( void )
{
	// calculate the no of pairs in graph
	int n = requirement[0]+requirement[1]+requirement[2]+requirement[3] + 1;
	// create a structure for graph
	struct node
	{
		int house_no;
		int warehouse_no;
		int distance;
	}graph[n];
	int i,j,k;
	// initialize graph by inputting start
	graph[0].house_no = -1;
	graph[0].warehouse_no = -1;
	graph[0].distance = 0;
	// fill in the nodes of graph
	k = 1;
	for(i = 0;i < 8;++i)
	{
		if(material[i] != -1)
		{
			graph[k].house_no = i/2;
			graph[k].warehouse_no = material[i];
			graph[k].distance = get_distance(i/2, material[i]);
			++k;
			
		}
	}
	// compute weight matrix
	int weight[n][n];
	//printf("\n");
	for(i = 0;i < n;++i)
	{
		for(j = 0;j < n;++j)
		{
			if( (i == j) || (j == 0) )
			{
				weight[i][j] = INFT;
			}
			else
			{
				weight[i][j] = get_distance(graph[i].house_no, graph[j].warehouse_no) + graph[j].distance;
			}
			
		}
	}
	//calculate path
	
	struct path
	{
		int branch;
		int branches_left;
		int distance;
	};
	struct path path[n];
	int final_path[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int visited[n],min,branches_to_visit = 0,tot_dist1 = 0,tot_dist2,temp;
	for(i = 0;i < n;++i)
	{
		visited[i] = 0;
	}
	i = 5;
	for(k = 0;k < n-1;++k)
	{
		min = 100;
		for(j = 1;j < n;++j)
		{
			if(i == j)
			continue;
			else if(visited[j] == 0)
			{
				if(min == weight[i][j])
				{
					++path[k].branches_left;
					path[k].branch = j;
				}
				else if(min > weight[i][j])
				{
					min = weight[i][j];
					path[k].branch = j;
					path[k].branches_left = 0;
				}
			}
		}
		i = path[k].branch;
		visited[i] = 1;
		branches_to_visit =branches_to_visit + path[k].branches_left;
		path[k].distance = min;
		tot_dist1 = tot_dist1 + min;
	}
	for(k = 0;k < n-1;++k)
	{
		final_path[k] = path[k].branch;
	}
	tot_dist2 = tot_dist1;
	while(branches_to_visit > 0)
	{
		k = n - 2;
		while(path[k].branches_left == 0 && k > 0)
		{
			visited[path[k].branch] = 0;
			tot_dist1  = tot_dist1 - path[k].distance;
			--k;
		}
		--branches_to_visit;
		visited[path[k].branch] = 0;
		temp = path[k].branches_left-1;
		--path[k].branches_left;
		i = path[k-1].branch;
		for(j = 1;j < n && temp >= 0;++j)
		{
			if(i == j)
			continue;
			else if(weight[i][j] == path[k].distance && visited[j] == 0)
			{
				--temp;
			}
		}
		path[k].branch = j-1;
		i = j-1;
		visited[i] = 1;
		++k;
		for(;k < n-1;++k)
		{
			min = 100;
			for(j = 1;j < n;++j)
			{
				if(i == j)
				continue;
				else if(visited[j] == 0)
				{
					if(min == weight[i][j])
					{
						++path[k].branches_left;
						path[k].branch = j;
					}
					else if(min > weight[i][j])
					{
						min = weight[i][j];
						path[k].branch = j;
						path[k].branches_left = 0;
					}
				}
			}
			i = path[k].branch;
			visited[i] = 1;
			branches_to_visit =branches_to_visit + path[k].branches_left;
			path[k].distance = min;
			tot_dist1 = tot_dist1 + min;
		}
		for(k = 0;k < n-1;++k)
		{
			final_path[k] = path[k].branch;
		}
		tot_dist2 = tot_dist1;
		if(tot_dist2 > tot_dist1)
		{
			for(k = 0;k < n-1;++k)
			{
				final_path[k] = path[k].branch;
			}
			tot_dist2 = tot_dist1;
		}
	}
	for(k = 0;k < n-1;++k)
	{
		final_path[k] = path[k].branch;
	}
	for(k = 0;k < n;++k)
	{
		node[k].warehouse = graph[final_path[k]].warehouse_no;
		node[k].house = graph[final_path[k]].house_no;
	}
	for(;k < 10;++k)
	{
		node[k].warehouse = -1;
		node[k].house = -1;
	}
	H5_path();
}


/*
* Function Name ::  void house_to_warehouse( int house_no, int warehouse_no, int mode )
* Input  :: house_no -> name of house at wich the bot is currently located ( -1 :: START, 0 :: H1, 1 :: H2, 2 :: H3, 3 :: H4, 4 :: H5 )
*			warehouse_no -> name of warehouse to which the bot must go ( 0 :: RED, 1 :: BLACK, 2 :: PINK, 3 :: BROWN, 4 :: GREEN, 5 :: BLUE )
*			mode -> whether the bot is visiting the warehouse for the first time or not and pick the appropriate CM from the warehouse ( 0 :: first time, 1 :: second time )
* Output :: void
* Logic  :: traverses the predefined path from the given house to warehouse and picks the CM
* Example Call  :: house_to_wareouse( 0, 2, 1 );
*/
void house_to_warehouse(int house_no, int warehouse_no, int mode) // MODE = 0 :: PICKING FIRST TIME, MODE = 1 :: PICKING UP SECOND TIME
{
	// ################## ALWAYS PICK FIRST CM FROM OUTER SIDE AND SECOND FROM INNER #################
	
	switch(house_no)
	{
		case 0:switch(warehouse_no)
		{
			case 0: back(); // GO FROM H1 TO RED
					_delay_ms(400);
					right_turn_180();
					wall_forward();
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(120);
						left();
						_delay_ms(80);
						stop();
						
						line_follow_dist_forward(225);
						
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(225);
						
					}
					pick();
					break;
			
			case 1: back(); // GO FROM H1 TO BLACK
					right_turn_180();
					line_follow_dist_forward(580);
					wall_forward();
					OCR4C = 300;
					_delay_ms(150);
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(325);
						
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(310);
					
					}
					pick();
					break;
			
			case 2: back(); //GO FROM H1 TO PINK
					_delay_ms(400);
					OCR4C = 412;
					right_turn_180(); 
					line_follow_dist_forward(580);
					wall_forward();
					OCR4C = 300;
					_delay_ms(150);
					left_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(320);
						
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(310);
					}
					pick();
					break;
			
			case 3: back(); // GO FROM H1 TO BROWN
					_delay_ms(400);
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(310);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(310);
					}
					pick();
					break;
			
			case 4: back(); // GO FROM H1 TO GREEN
					_delay_ms(400);
					stop();
					right_turn_90();
					forward_node(1);
					line_follow_dist_forward(70);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(160);
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(310);
						right();
						
					}
					pick();
					break;
			
			case 5: back(); // GO FROM H1 TO BLUE
					_delay_ms(400);
					stop();
					right_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(310);
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(310);
						
					}
					pick();
					break;
		}
		break;
		case 1:switch(warehouse_no)
		{
			case 0: back(); // GO FROM H2 TO RED
					_delay_ms(300);
					stop();
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(280);
						left();
						_delay_ms(50);
						stop();
						
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(250);
						
					}
					pick();
					break;
			
			case 1: back();// GO FROM H2 TO BLACK
					_delay_ms(400);
					stop();
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(325);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(300);
						right();
						_delay_ms(50);
						stop();
					}
					pick();
					break;
			
			case 2: back(); // GO FROM H2 TO PINK
					_delay_ms(400);
					stop();
					left_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(325);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(300);
						right();
						_delay_ms(50);
						stop();
					}
					pick();
					break;
			
			case 3: back(); // GO FROM H2 TO BROWN
					_delay_ms(400);
					stop();
					right_turn_180();
					wall_forward();
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			
			case 4: back(); // GO FROM H2 TO GREEN
					_delay_ms(400);
					stop();
					right_turn_180();
					wall_forward();
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(300);
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			
			case 5: back(); // GO FROM H2 TO BLUE
					_delay_ms(400);
					stop();
					right_turn_180(); 
					wall_forward();
					right_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(300);
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
		}
		break;
		case 2:switch(warehouse_no)
		{
			case 0: back(); // GO FROM H3 TO RED
					_delay_ms(400);
					stop();
					right_turn_180();
					zig_zag(1);
					right_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(325);
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			
			case 1: back(); // GO FROM H3 TO BLACK
					_delay_ms(400);
					stop();
					right_turn_180();
					zig_zag(1);
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(325);
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			
			case 2: back(); // GO FROM H3 TO PINK
					_delay_ms(400);
					stop();
					right_turn_180();
					zig_zag(1);
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(325);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(260);
						left();
						_delay_ms(50);
						stop();
					}
					pick();
					break;
			
			case 3: back(); // GO FROM H3 TO BROWN
					_delay_ms(400);
					stop();
					left_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(325);
						right();
						_delay_ms(50);
						stop();
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(280);
					}
					pick();
					break;
			
			case 4: back(); // GO FROM H3 TO GREEN
					_delay_ms(400);
					stop();
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(300);
						
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			
			case 5: back(); // GO FROM H3 TO BLUE
					_delay_ms(400);
					stop();
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(315);
						for( i = 0; i < 5000; ++i )
						{
							right();
						}
						stop();
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
		}
		break;
		case 3:switch(warehouse_no)
		{
			case 0: back(); // GO FROM H4 TO RED
					_delay_ms(400);
					stop();
					right_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(335);
						right();
						_delay_ms(50);
						stop();
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
						right();
						_delay_ms(40);
						stop();
					}
					pick();
					break;
			
			case 1: back(); // GO FROM H4 TO BLACK
					_delay_ms(400);
					stop();
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(150);
						left();
						_delay_ms(50);
						stop();
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(200);
						//right();
						//_delay_ms(40);
						//stop();
					}
					pick();
					break;
			
			case 2: back(); // GO FROM H4 TO PINK
					_delay_ms(350);
					stop();
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(200);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			
			case 3: back(); // GO FROM H4 TO BROWN
					_delay_ms(400);
					stop();
					right_turn_180();
					zig_zag();
					left_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(300);
						left();
						_delay_ms(70);
						stop();
					}
					pick();
					break;
			case 4: back(); // GO FROM H4 TO GREEN
					_delay_ms(400);
					stop();
					right_turn_180();
					zig_zag();
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			
			case 5: back(); // GO FROM H4 TO BLUE
					_delay_ms(400);
					stop();
					right_turn_180();
					zig_zag();
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(300);
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
		}
		break;
		case 4:switch(warehouse_no)
		{
			case 0: white_node(1, 1, 0);// GO FROM H5 TO RED
					right_turn_90();
					forward_node(5);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(325);
						right();
						_delay_ms(30);
						stop();
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			case 1: white_node(1, 1, 0); // GO FROM H5 TO BLACK
					right_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(230);
						left();
						_delay_ms(25);
						stop();
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(280);
					}
					pick();
					break;
			case 2: white_node(1, 1, 0);// GO FROM H5 TO PINK
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(325);
						right();
						_delay_ms(30);
						stop();
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(300);
					}
					pick();
					break;
			case 3: white_node(1, 1, 1);// GO FROM H5 TO BROWN
					left_turn_90();
					forward_node(5);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(325);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(320);
						right();
						_delay_ms(25);
						stop();
					}
					pick();
					break;
			case 4: white_node(1, 1, 1);// GO FROM H5 TO GREEN
					left_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(200);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(200);
						right();
						_delay_ms(45);
						stop();
					}
					pick();
					break;
			case 5: white_node(1, 1, 1);// GO FROM H5 TO BLUE
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(215);
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(320);
						right();
						_delay_ms(25);
						stop();
					}
					pick();
					break;
		}
		break;
		default:switch(warehouse_no)
		{
			case 0: forward_node(1);		// GO FROM START TO RED
					left_turn_90();
					forward_node(1);
					left_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(275);
						for (i = 0; i < 30000; ++i)
						{
							right();
							
						}
						stop();
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(345);
						right();
						delay_ms(150);
						stop();
						left();
						delay_ms(50);
						stop();
						
						
					}
					pick();
					break;
			
			case 1: forward_node(1);		// GO FROM START TO BLACK
					left_turn_90();
					forward_node(1);
					left_turn_90();
					forward_node(3);
					servo_rotate(0, 370);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(275);
						for (i = 0; i < 30000; ++i)
						{
							right();
							
						}
						stop();
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(345);
						right();
						_delay_ms(50);
						stop();
						
					}
					pick();	
					break;
			
			case 2: forward_node(1);		// GO FROM START TO PINK
					left_turn_90();
					forward_node(1);
					left_turn_90();
					forward_node(5);
					if( mode == 0 )
					{
						right_turn_90();
						line_follow_dist_forward(225);
						right();
						_delay_ms(50);
						stop();
						
					}
					else
					{
						left_turn_90();
						line_follow_dist_forward(345);
						right();
						_delay_ms(50);
						stop();
						
					}
					pick();
					break;
			
			case 3: forward_node(1);		// GO FROM START TO BROWN
					right_turn_90();
					forward_node(1);
					right_turn_90();
					forward_node(1);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(295);
						left();
						_delay_ms(5);
						stop();
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(185);
						right();
						_delay_ms(20);
						stop();
						
					}
					pick();
					break;
			
			case 4: forward_node(1);		// GO FROM START TO GREEN
					right_turn_90();
					forward_node(1);
					right_turn_90();
					forward_node(3);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(345);
						right();
						_delay_ms(50);
						stop();
						
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(325);
						right();
						_delay_ms(50);
						stop();
						
					}
					pick();
					break;
			
			case 5: forward_node(1);		// GO FROM START TO BLUE
					right_turn_90();
					forward_node(1);
					right_turn_90();
					forward_node(5);
					if( mode == 0 )
					{
						left_turn_90();
						line_follow_dist_forward(345);
						right();
						_delay_ms(50);
						stop();
						
					}
					else
					{
						right_turn_90();
						line_follow_dist_forward(305);
						right();
						_delay_ms(50);
						stop();
						
					}
					pick();
					break;
		}
		
	}
}


/*
* Function Name ::  void warehouse_to_house( int warehouse_no, int house_no, int mode )
* Input  :: warehouse_no -> name of warehouse to which the bot must go ( 0 :: RED, 1 :: BLACK, 2 :: PINK, 3 :: BROWN, 4 :: GREEN, 5 :: BLUE )
*			house_no -> name of house at wich the bot is currently located ( 0 :: H1, 1 :: H2, 2 :: H3, 3 :: H4, 4 :: H5 )
*			mode -> whether the bot has picked the CM from the outer side of the arena or inner side( 1 :: outer side, 2 :: inner side )
* Output :: void
* Logic  :: traverses the predefined path from the given warehouse to house and places the CM
* Example Call  :: warehouse_to_wareouse( 0, 2, 1 );
*/
void warehouse_to_house(int warehouse_no, int house_no, int mode)
{
	switch(warehouse_no)
	{
		case 0:switch(house_no)
		{
			case 0: line_follow_dist_forward(268); // RED TO H1
					if( mode == 1 )
					{
						right_turn_90();
						servo_rotate(0, 370);
						forward_node(1);
						for( i = 0; i < 65000; ++i )
						{
							forward();
						}
						stop();
						right_turn_90();
					}
					else
					{
						left_turn_90();
						servo_rotate(0, 370);
						forward_node(1);
						left_turn_90();
					}
					forward_node(1);
					left_turn_90();
					wall_forward();
					place( floor_array[house_no], 2 );
					break;
			
			case 1: line_follow_dist_forward(200); // RED TO H2
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(1);
					place( floor_array[house_no], 1);
					break;
			
			case 2: line_follow_dist_forward(100); // RED TO H3
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(3);
					left_turn_90();
					zig_zag();
					place( floor_array[house_no], 2);
					break;
			
			case 3: line_follow_dist_forward(200); // RED TO H4
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(3);
					right();
					_delay_ms(50);
					stop();
					place( floor_array[house_no], 1);
					break;
			
			case 4: line_follow_dist_forward(200); // RED TO H5
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(5);
					left_turn_90();
					white_node(0,floor_array[4], 0);
					break;
		}
		break;
		case 1:switch(house_no)
		{
			case 0: line_follow_dist_forward(200); // BLACK TO H1
					if( mode == 1 )
					{
						if( floor_array[1] == 0 )
							left_turn_90();
						else
							right_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					right_turn_90();
					wall_forward();
					place( floor_array[house_no], 2);
					break;
			
			case 1: line_follow_dist_forward(200); // BLACK TO H2
					if( mode == 1 )
					{
						if( floor_array[1] == 0 )
							left_turn_90();
						else
							right_turn_90();
						forward_node(1);
						servo_rotate(0, 450);
						left_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					place( floor_array[house_no], 0);
					break;
			
			case 2: line_follow_dist_forward(200); // BLACK TO H3
					if( mode == 1 )
					{
						if( floor_array[1] == 0 )
							left_turn_90();
						else
							right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(1);
					left_turn_90();
					zig_zag();
					back();
					_delay_ms(130);
					stop();
					place( floor_array[house_no], 2);
					break;
			
			case 3: line_follow_dist_forward(200); // BLACK TO H4
					if( mode == 1 )
					{
						if( floor_array[1] == 0 )
							left_turn_90();
						else
							right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(1);
					place( floor_array[house_no], 1);
					break;
			case 4: line_follow_dist_forward(200); // BLACK TO H5
					if( mode == 1 )
					{
						if( floor_array[1] == 0 )
							left_turn_90();
						else
							right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(3);
					left_turn_90();
					white_node(0,floor_array[4], 0);
					break;
		}
		break;
		case 2:switch(house_no)
		{
			case 0: line_follow_dist_forward(200); // PINK TO H1
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(3);
					right_turn_90();
					wall_forward();
					place( floor_array[house_no], 2);
					break;
			
			case 1: line_follow_dist_forward(200); // PINK TO H2
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(3);
					place( floor_array[house_no], 0);
					break;
			
			case 2: line_follow_dist_forward(120); // PINK TO H3
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					right_turn_90();
					zig_zag();
					back();
					_delay_ms(130);
					stop();
					place( floor_array[house_no], 2);
					break;
			case 3: line_follow_dist_forward(200); // PINK TO H4
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					place( floor_array[house_no], 0);
					break;
			
				case 4: line_follow_dist_forward(200); // PINK TO H5
						if( mode == 1 )
						{
							left_turn_90();
							forward_node(1);
							right_turn_90();
						}
						else
						{
							right_turn_90();
							forward_node(1);
							left_turn_90();
						}
						forward_node(1);
					left_turn_90();
					white_node(0,floor_array[4], 0);
					break;
		}
		break;
		case 3:switch(house_no)
		{
			case 0: line_follow_dist_forward(200); // BROWN TO H1
					if( mode == 1 )
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					place( floor_array[house_no], 0);
					break;
			
			case 1: line_follow_dist_forward(200); // BROWN TO H2
					if( mode == 1 )
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					right_turn_90();
					wall_forward();
					place( floor_array[house_no], 2);
					break;
					
			case 2: line_follow_dist_forward(200); // BROWN TO H3
					if( mode == 1 )
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(3);
					place( floor_array[house_no], 0);
					break;
			
			case 3: line_follow_dist_forward(200); // BROWN TO H4
					if( mode == 1 )
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(3);
					right_turn_90();
					zig_zag();
					place( floor_array[house_no], 2);
					break;
			
			case 4: line_follow_dist_forward(200); // BROWN TO H5
					if( mode == 1 )
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(5);
					right_turn_90();
					white_node(0,floor_array[4], 1);
					break;
		}
		break;
		case 4:switch(house_no)
		{
			case 0: line_follow_dist_forward(200); // GREEN TO H1
					if( mode == 1 )
					{
						if( floor_array[2] == 0 )
							right_turn_90();
						else
							left_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(1);
					forward_node(1);
					right_turn_90();
					forward_node(1);
					place( floor_array[house_no], 1);
					break;
			
			case 1: line_follow_dist_forward(200); // GREEN TO H2
					if( mode == 1 )
					{
						if( floor_array[2] == 0 )
						right_turn_90();
						else
						left_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(1);
					left_turn_90();
					wall_forward();
					place( floor_array[house_no], 2);
					break;
					
			case 2: line_follow_dist_forward(200); // GREEN TO H3
					if( mode == 1 )
					{
						if( floor_array[2] == 0 )
						right_turn_90();
						else
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					place( floor_array[house_no], 0);
					break;
			case 3: line_follow_dist_forward(200); // GREEN TO H4
					if( mode == 1 )
					{
						if( floor_array[2] == 0 )
						right_turn_90();
						else
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					right_turn_90();
					zig_zag();
					place( floor_array[house_no], 2);
					break;
			
			case 4:line_follow_dist_forward(200); // GREEN TO H5
					if( mode == 1 )
					{
						if( floor_array[2] == 0 )
							right_turn_90();
						else
							left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(3);
					right_turn_90();
					white_node(0, floor_array[4], 1);
					break;
		}
		break;
		case 5:switch(house_no)
		{
			case 0: line_follow_dist_forward(200); // BLUE TO H1
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(3);
					place( floor_array[house_no], 1);
					break;
			
			case 1: line_follow_dist_forward(200); // BLUE TO H2
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(3);
					left_turn_90();
					wall_forward();
					place( floor_array[house_no], 2);
					break;
					
			case 2: line_follow_dist_forward(200); // BLUE TO H3
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(1);
					place( floor_array[house_no], 1);
					break;
					
			case 3: line_follow_dist_forward(200); // BLUE TO H4
					if( mode == 1 )
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					else
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					forward_node(1);
					left_turn_90();
					zig_zag();
					place( floor_array[house_no], 2);
					break;
					
			case 4: line_follow_dist_forward(200); // BLUE TO H5
					if( mode == 1 )
					{
						left_turn_90();
						forward_node(1);
						left_turn_90();
					}
					else
					{
						right_turn_90();
						forward_node(1);
						right_turn_90();
					}
					forward_node(1);
					right_turn_90();
					white_node(0, floor_array[4], 1);
					break;
		}
	}
}

/*
* Function Name ::  void task5( void )
* Input  :: void
* Output :: void
* Logic  :: traverses the path as stored in the path structure and performs the given task
* Example Call  :: task5();
*/
void task5( void )
{
	find_shortest_path_with_H5(); // GET SHORTEST PATH AND STORE IN GLOBAL VARIABLE
	pin_init(); // INITIALIZE ALL PINS OF MICROCONTROLLER
	int warehouse_visited[6] = {0,0,0,0,0,0}; // INITIALIZE ARRAY FOR STORING WHETHER THE WAREHOUSE HAS BEEN VISITED OR NOT
	
	int n = requirement[0]+requirement[1]+requirement[2]+requirement[3]+requirement[4]; // GET THE TOTAL NUMBER OF DELIVERIES TO BE MADE
	
	int CURR_HOUSE; // VARIABLE FOR STORING THE LOCATION OF THE CURRENT HOUSE THE BOT IS ON
	int NEXT_WAREHOUSE; // VARIABLE TO STORE THE LOCATION OF NEXT WAREHOUSE THE BOT MUST GO TO
	int NEXT_HOUSE; // VARIABLE FOR STORING THE LOCATION OF NEXT HOUSE THE BOT MUST VISIT
	
	CURR_HOUSE = -1; // SET THE CURRENT LOCATION OF THE BOT TO 'START'
	NEXT_WAREHOUSE = node[0].warehouse; // SET THE NEXT WAREHOUSE TO BE VISITED AS THE ONE STORED IN THE SHORTEST PATH ALGORITHM
	NEXT_HOUSE = node[0].house; // STORE THE CORRESPONDING HOUSE OF THE WAREHOUSE IN THE PATH
	
	for( int i = 0; i < n ; ++i) // REPEAT THE FOLLOWING FOR ALL NODE OF THE SHORTEST PATH
	{
		house_to_warehouse(CURR_HOUSE, NEXT_WAREHOUSE, warehouse_visited[ NEXT_WAREHOUSE ]); // GO FROM THE CURRENT HOUSE TO THE NEXT WAREHOUSE
		++warehouse_visited[ NEXT_WAREHOUSE ]; // MARK THIS WAREHOUSE AS VISITED	
		warehouse_to_house( NEXT_WAREHOUSE, NEXT_HOUSE, warehouse_visited[ NEXT_WAREHOUSE ]); // GO FROM THE CURRENT WAREHOUSE TO THE HOUSE THE CM IS TO BE DELIVERED TO
		CURR_HOUSE = NEXT_HOUSE; // SET THIS HOUSE AS THE CURRENT HOUSE
		NEXT_WAREHOUSE = node[i+1].warehouse; // STORE THE LOCATION OF NEXT WAREHOUSE IN THE PATH AS THE NEXT WAREHOUSE
		NEXT_HOUSE = node[i+1].house; // STORE THE CORRESPONDING HOUSE OF THE WAREHOUSE AS THE NEXT HOUSE
	}
	
	buzzer_5(); // SOUND THE BUZZER FOR SIGNALLING THE END OF THE TASK
}
