all: encrypt

encrypt: main.o hostapd/crypto/libcrypto.a
	$(CC)  main.o -o encrypt -lstdc++ -l:hostapd/crypto/libcrypto.a

main.o: main.cpp
	$(CC) main.cpp -c

hostapd/crypto/libcrypto.a:
	(cd hostapd/crypto && make -j24)

clean:
	rm main.o
	rm -rf encrypt