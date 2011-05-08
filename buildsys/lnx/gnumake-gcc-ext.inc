# build class specific settings

TARGET=$(TARGETPATH)/$(TARGETNAME)
INSTTARGET=$(TARGET)

INCPATH += -I$(FLEXTINC)
LIBPATH += -L$(FLEXTLIB)

#ifdef SHARED
#LIBS += -l$(FLEXTNAME).$(FLEXTMAJOR).$(FLEXTMINOR)
#else
LIBS += -l$(FLEXTNAME)
#endif

##############################################

# default target
_build_: $(TARGET)

$(CSRCS) $(CPPSRCS): $(patsubst %,$(SRCDIR)/%,$(HDRS))
	touch $@

$(TARGETPATH):
	mkdir -p $@

$(TARGETPATH)/%.opp : $(SRCDIR)/%.cpp
	$(CXX) -c $(CFLAGS) $(DEFS) $(INCPATH) $< -o $@

$(TARGETPATH)/%.o : $(SRCDIR)/%.c
	$(CC) -c $(CFLAGS) $(DEFS) $(INCPATH) $< -o $@

$(TARGET):: $(TARGETPATH)

$(TARGET):: $(COBJS) $(CPPOBJS)
	$(CXX) $(LDFLAGS) $(LIBPATH) -o $@ $(COBJS) $(CPPOBJS) $(LIBS)
	chmod 755 $@
ifndef DEBUG
ifndef PROFILE
	strip --strip-unneeded $@
endif
endif

##############################################

_clean_:
	-rm -r $(TARGETPATH)

##############################################

$(INSTPATH):
	-mkdir -p $@

_install_: $(INSTPATH)
	install $(TARGET) $(INSTPATH)