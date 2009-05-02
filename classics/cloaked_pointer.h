// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\cloaked_pointer.h
// Revision: public build 9, shipped on 18-Oct-2006


namespace classics {


template <typename T, unsigned int key>
class cloaked_pointer {
   unsigned int disguise;
   static unsigned int hide (T* p);
   static T* reveal (unsigned int x);
public:
   cloaked_pointer (T* p = 0) : disguise(hide(p)) {}
   cloaked_pointer (const cloaked_pointer<T,key>& other) : disguise(other.disguise) {}
   ~cloaked_pointer() { disguise= hide((T*)0); }
   cloaked_pointer<T,key> operator= (const cloaked_pointer<T,key>& other) { disguise= other.disguise; return *this; }
   T* operator* () { return reveal (disguise); }
   const T* operator* () const { return reveal (disguise); }
   T* operator-> () const { return reveal (disguise); }
   operator T* () const { return reveal (disguise); }

   };


template <typename T, unsigned int key>
unsigned int cloaked_pointer<T,key>::hide (T* p)
 {
 return ((reinterpret_cast<unsigned int>(p)) >> 2) ^ key;
 }

template <typename T, unsigned int key>
T* cloaked_pointer<T,key>::reveal (unsigned int x)
 {
 return reinterpret_cast<T*>((x^key)<<2);
 }

}

