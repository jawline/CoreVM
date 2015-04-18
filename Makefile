execute_makefiles:
	@for a in $$(ls); do \
		if [ -d $$a ]; then \
			echo "processing folder $$a"; \
			$(MAKE) -C $$a $(MAKE_TARGET); \
	fi; \
	done;
	@echo "Done!"


all: execute_makefiles

install: MAKE_TARGET += install
install: execute_makefiles

clean: MAKE_TARGET += clean
clean: execute_makefiles