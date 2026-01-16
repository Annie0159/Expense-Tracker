all:
	export DYLD_LIBRARY_PATH=/usr/local/opt/openssl@3/lib:/usr/local/mysql-connector-c++-9.4.0/lib64:$$DYLD_LIBRARY_PATH; \
	export PATH=/usr/local/bin:/opt/homebrew/bin:$$PATH; \
	g++ -std=c++17 -Iinclude -I/usr/local/mysql-connector-c++-9.4.0/include \
	src/*.cpp \
	-L/usr/local/mysql-connector-c++-9.4.0/lib64 -Wl,-rpath,/usr/local/mysql-connector-c++-9.4.0/lib64 \
	-lmysqlcppconn8.2 -o app && ./app
