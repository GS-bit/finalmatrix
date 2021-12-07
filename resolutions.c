void gauss_jordan(unsigned int n, double system[n][n+1]){
	double m;
	int condition_return;

	/* p means pivot */
	for(int p = 0; p < n; p++){
		/* Permutation: */
			
		if(system[p][p] == 0){
			int flag = 0;
			int health_line_index;
			
			for(int i = 0; i < n; i++){
				if(system[i][p] != 0){
					flag = 1;
					health_line_index = i;
				}
			}
			
			if(flag){
				double aux[n+1];
				
				for(int i = 0; i < n+1; i++){
					aux[i] = system[p][i]; /* aux now has the problematic line */
				}
				
				for(int i = 0; i < n+1; i++){
					system[p][i] = system[health_line_index][i]; /* the problematic line now has the health line */
					system[health_line_index][i] = aux[i]; /* health line now has the problematic line */
				}
			}
		}
		
		/* Multiply the line containing the pivot: */
		
		m = system[p][p];

		for(int j = 0; j < n+1; j++){
			system[p][j] /= m; 
		}

		/* Sum the other lines: */

		for(int i = 0; i < n-1; i++){
			condition_return = p+i+1 > n-1 ? p+i-(n-1) : p+i+1;
			m = system[condition_return][p];

			for(int j = 0; j < n+1; j++){
				system[condition_return][j] -= (m * system[p][j]);
			}
		}
	}
}
