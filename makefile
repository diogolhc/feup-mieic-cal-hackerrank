all: capital weights palindromes highway paddyfield router saving

capital: capital.cpp
	g++ -Wall -std=c++14 -o capital capital.cpp

weights: weights.cpp
	g++ -Wall -std=c++14 -o weights weights.cpp

palindromes: palindromes.cpp
	g++ -Wall -std=c++14 -o palindromes palindromes.cpp

highway: highway.cpp
	g++ -Wall -std=c++14 -o highway highway.cpp

paddyfield: paddyfield.cpp
	g++ -Wall -std=c++14 -o paddyfield paddyfield.cpp

router: router.cpp
	g++ -Wall -std=c++14 -o router router.cpp

saving: saving.cpp
	g++ -Wall -std=c++14 -o saving saving.cpp


clean:
	rm -f capital weights palindromes highway paddyfield router saving
