// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=casts.h
// Revision: public build 4, shipped on 29-Aug-98

//This is not inside the namespace, so I don't have to qualify the names.
//MS VC++5.0 (still) has problems with using declarations on template names.

template <typename BaseH, typename DerivedH>
BaseH implicit_handle_cast (DerivedH dh)
 {
 return BaseH (dh.operator->());
 }

template <typename BaseH, typename DerivedH>
BaseH dynamic_handle_cast (DerivedH dh)
 {
 return BaseH (dynamic_cast<typename BaseH::Type*> (dh.operator->()));
 }

template <typename BaseH, typename DerivedH>
BaseH static_handle_cast (DerivedH dh)
 {
 return BaseH (static_cast<typename BaseH::Type*> (dh.operator->()));
 }

template <typename BaseH, typename DerivedH>
BaseH reinterpret_handle_cast (DerivedH dh)
 {
 return BaseH (reinterpret_cast<typename BaseH::Type*> (dh.operator->()));
 }

template <typename BaseH, typename DerivedH>
BaseH const_handle_cast (DerivedH dh)
 {
 return BaseH (const_cast<typename BaseH::Type*> (dh.operator->()));
 }

