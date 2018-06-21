/* Home Entertainment Company's SW Development Team plans to assign the projects to help the new developer Gram Park gain as much experience as possible.
However, the team is contemplating how to assign projects to Gram Park since it is not desirable to assign multiple projects at the same time or assign a next project as soon as she finishes the previous one.

[Requirement]
When the starting date S and the ending date E of a project are given, the project schedule overlap can be determined as shown in the figure below.
Assign projects for Gram Park to participate in as many projects as possible to gain experience.


[Input Format]

N, the number of projects planned for the team is input.

(N is a natural number and 2<= N <= 15.)

The project data are input in each of next N lines.

The project data have the starting date S and the ending date E with a space between them (1 <= S <= E <= 300).

The project data may not be sorted by the starting date or the ending date.

There can be multiple projects having the same starting date and the ending date.

[Output Format]
Output the maximum number of project that can be assigned to Gram Park without overlapping.

Input / Output Examples
⋇ Please keep the input/output format.
Input Example 1
3
1 3
2 6
5 7
Output Example 1
2

Input Example 2
5
1 3
5 10
11 20
23 31
40 70
Output Example 2
5

Input Example 3
6
8 11
4 6
3 15
17 30
19 21
23 33
Output Example 3
4

Input Example 4
10
8 11
4 6
40 45
3 15
82 150
17 30
19 21
23 33
34 80
60 70
Output Example 4
7

Input Example 5
10
42 44
45 55
115 119
9 12
138 152
156 161
157 169
157 168
36 38
18 24
Output Example 5
8

Input Example 6
12
46 46
15 18
23 27
34 36
9 14
48 48
30 30
34 38
18 19
26 26
30 33
3 6
Output Example 6
8

Input Example 7
13
124 128
62 73
44 52
68 72
33 50
18 37
14 15
100 118
97 112
91 93
29 35
71 73
25 33
Output Example 7
7

Input Example 8
14
180 185
153 167
32 48
1 9
55 67
49 58
112 125
91 99
26 41
24 33
109 112
105 106
48 64
15 23
Output Example 8
9

Input Example 9
15
50 61
214 219
20 38
45 45
118 144
214 220
182 187
85 107
111 120
158 161
38 50
7 7
142 148
136 153
116 120
Output Example 9
10

Input Example 10
15
132 144
51 81
42 46
187 217
168 199
68 85
118 125
194 217
126 155
230 300
42 70
183 209
207 237
34 42
121 152
Output Example 10
6 */
#include <stdio.h>

#define MAX_PROJECT (15)
typedef struct{
	int start_date; // Start date
	int end_date; // End date
}DATA;

int     N; // Number of projects
DATA    project_info[MAX_PROJECT]; // Project Infomation

void Data_Input(void){
	int i;
	scanf("%d", &N); // Input of number of projects

	// Input of project information
	for (i = 0; i < N; i++){
		scanf("%d %d", &project_info[i].start_date, &project_info[i].end_date);
	}
}
void sortByStartDate(void){
	for(int i=0;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			if(project_info[i].start_date > project_info[j].start_date)
			{
				DATA temp;
				temp = project_info[i];
				project_info[i] = project_info[j];
				project_info[j] = temp;
			}
		}
	}
}


int main(void){
	int sol=0;

	Data_Input(); // Calling of input function
	sortByStartDate();
	for(int i=0;i<N-1;i++)
	{
		//printf("%d , ",project_info[i].start_date);
		if(project_info[i].end_date < project_info[i+1].start_date )
			sol++;
	}

	printf("%d\n", sol+1); // Output of result
	return 0;
}
