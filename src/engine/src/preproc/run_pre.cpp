#include "run_pre.h"

int run_preprocessing(Context &context) {
	cout << "##### PREPROCESSING START #####" << endl;

	clock_t begin, end;
	//new Preproc

	begin = clock();

	std::cerr << "=== init Context ===" << std::endl;
	Preproc_new preN(context);

	std::cerr << "=== SET MAP INFO ===" << std::endl;
	preN.setMapInfo(context.grammar.getMapInfo(), context.grammar.getErules());

	std::cerr << "=== COUNT NUM ===" << std::endl;
	preN.countNum(context);

	std::cerr << "=== SET VIT ===" << std::endl;
	preN.setVIT(context);

	std::cerr << "=== DDM_SETNUMPARTS ===" << std::endl;
	context.ddm.setNumPartition(context.getNumPartitions());

	std::cerr << "=== DDM_RESIZE ===" << std::endl;
	context.ddm.reSize();

	std::cerr << "=== SAVE DATA ===" << std::endl;
	preN.saveData(context);

	std::cerr << "=== MERGEPART ===" << std::endl;
	preN.mergePart(context);
	//preN.test_saveData(context);
	//preN.test_mergePart(context);
	end = clock();
	cout << "NEWPREPROC TIME: " << ((end - begin) / CLOCKS_PER_SEC) << std::endl;
	return 0;
}
