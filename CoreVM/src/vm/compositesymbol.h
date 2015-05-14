#ifndef _COMPOSITE_SYMBOL_DEF_H_
#define _COMPOSITE_SYMBOL_DEF_H_

namespace VM {
  
  enum CompositeSymbolType {
    Scale, Add, AddValue, Reference
  };

  class CompositeSymbol {
  private:
  public:
    CompositeSymbol();
    virtual ~CompositeSymbol();
  };
}

#endif //_COMPOSITE_SYMBOL_DEF_H_
