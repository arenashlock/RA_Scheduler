compile:
	javac -d ./class ./src/*.java
	clear

run:
	java -cp ./class Algorithm

clean:
	rm -rf ./class
	clear