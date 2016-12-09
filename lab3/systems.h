


#pragma once


namespace system1 {

	static const unsigned int systemSize = 4;
	
	static double row1[systemSize] = { 13, 12, 3,  16 };
	static double row2[systemSize] = { 0,  28, 17, 10 };
	static double row3[systemSize] = { 9,  1,  14, 3  };
	static double row4[systemSize] = { 10, 14, 3,  0  };

	double* coeficients[systemSize]= {
		row1,
		row2,
		row3,
		row4
	};

	double constantTerms[systemSize] = {
		242,
		279,
		111,
		143
	};

}

namespace system2 {

	static const unsigned int systemSize = 4;

	static double row1[systemSize] = { 23, -2, -11, 6 }; // (1) - (2) + (4) 
	static double row2[systemSize] = { 0,  28, 17, 10 };
	static double row3[systemSize] = { 9,  1,  14, 3  };
	static double row4[systemSize] = { -3, 2, 0,  -16  }; // (4) - (1)

	double* coeficients[systemSize]= {
		row1,
		row2,
		row3,
		row4
	};

	double constantTerms[systemSize] = {
		106, // (1) - (2) + (4) 
		279,
		111,
		-99  // 
	};

}


namespace iterationSuitableSystemTest {

	const unsigned int systemSize = 3;


	double row1[systemSize] = { 72, -3,  16  };
	double row2[systemSize] = { 41, -92, 12  };
	double row3[systemSize] = { 10, -7,  -91 };

	double* coeficients[systemSize] = {
		row1,
		row2,
		row3
	};

	double constantTerms[systemSize] = {
		-1,
		60,
		-12
	};

}