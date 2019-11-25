build:
	gcc -Wall -Werror rncomponent.c -o rncomponent

test:
	make
	./rncomponent --js stateless
	./rncomponent --ts stateful
	./rncomponent --ts testButton
	./rncomponent --ts FancyClass
	./rncomponent --ts AmazingComponent
	./rncomponent --js example/stateless
	./rncomponent --ts example/stateful
	./rncomponent --ts example/testButton
	./rncomponent --ts example/FancyClass
	./rncomponent --ts example/AmazingComponent

clean:
	rm *.js
	rm *.tsx
	rm rncomponent
	rm example/*.js
	rm example/*.tsx
