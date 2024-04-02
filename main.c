#include <stdio.h>
#include <stdlib.h>

double calcSRTT(double alpha, double SRTT, double R);
double calcRTTVAR(double beta, double RTTVAR, double SRTT, double R);
double calcRTO(double SRTT, double G, double K, double RTTVAR);
double rounding(double g, double r);

int main(int argc, char* argv[]) {
	double G; //granularity
	double R = 1; //sample round trip time
	double SRTT; //smooth rtt
	double RTTVAR; //variation in rtt
	double RTO; //retransmission timeout 
	double ALPHA = 0.125; // alpha
	double BETA = 0.25; //beta
	double K;
	int X, C;	
	
	//CLA: first is granularity, second is minimum RTO, third is opptional, debugging flag
	if(argc == 1) {
		printf("Please enter granularity and rto as command line arguments\n");
	} else if (argc == 2) {
		printf("Please enter granularity and rto as command line arguments\n");
	}
	
	G = atof(argv[1]);	
	RTO = atof(argv[2]);
	X = 1;
	C = 0;	
	RTO = 1;
	K = 4;

	while(X != 0) {
		if(C == 0) {
			RTO = 1;
			SRTT = RTO;
			RTTVAR = RTO/2;
			
			//RTO = SRTT + MAX(G, K*RTTVAR);
		} else {
			printf("Enter RTT sample > ");
			scanf("%f", &R);	
			RTTVAR = calcRTTVAR(BETA, RTTVAR, SRTT, R);
			RTO = calcRTO(SRTT, G, K, RTTVAR);	
			SRTT = calcSRTT(ALPHA, SRTT, R);
			RTO = rounding(G, RTO);
		}
		printf("Enter 0 to exit: ");
		scanf("%d", &X);		
		printf("RTTVAR = %f\n", RTTVAR);
		printf("RTO = %f second(s)\n", RTO);
		printf("SRTT = %f\n\n", SRTT);
		printf("\n");
		C++;
	}	
}

/*

//take input of granularity
//input of minimum rto
//optional debugging flag
//option for a fine grained clock
//round up for clock granularity
//
//calc SRTT
//calc RTTVAR
//Calc new RTO
*/

double calcSRTT(double ALPHA, double SRTT, double R) {
	double x = 1 - ALPHA;	
	double asd = ALPHA * R;
	double y = x * SRTT;
	
	double calcSRTT = y + asd;	
	return calcSRTT;	
		
}

double calcRTTVAR(double BETA, double RTTVAR, double SRTT, double R){
	double b = 1 - BETA; 
	double x = abs(SRTT - R);
	double ab = BETA * x;
	double rttv = b * RTTVAR;
	
	double calcRTTVAR = rttv + ab;
	return calcRTTVAR;
}

double calcRTO(double SRTT, double G, double K, double RTTVAR){
	double kr = K*RTTVAR;
	if (kr < G) {
		kr = G;
	}	
		
	double calcRTO = SRTT + kr;
	return calcRTO;
}

double rounding(double g, double r) {
	int x, y;
	double z;
	double a = r/g;
	x = (int)a;
	z = a - x;	
	if( z > 0.5) {
		x++;
	}
	r = x*g;
	return r;
}
