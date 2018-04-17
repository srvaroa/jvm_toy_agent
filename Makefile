CC=g++
# in OSX, sample:
# /Library/Java/JavaVirtualMachines/jdk1.8.0_92.jdk/Contents/Home
AGENT=agent.so
BUILD_DIR=build

app: Test.java
	mkdir -p $(BUILD_DIR)
	javac Test.java -d $(BUILD_DIR)

agent:
	$(CC) -Wall -shared \
		-o $(BUILD_DIR)/$(AGENT) \
		-I $(JAVA_HOME)/include \
		-I $(JAVA_HOME)/include/darwin \
		agent.cc

run: app agent
	java -agentpath:$(PWD)/$(BUILD_DIR)/$(AGENT) -cp $(BUILD_DIR)/ Test

clean:
	if test -d $(BUILD_DIR); \
	then rm -r $(BUILD_DIR); \
	fi
