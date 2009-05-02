// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\debug_object_count.h
// Revision: public build 9, shipped on 18-Oct-2006

class debug_object_count_t {
public:
   debug_object_count_t();   // not exported, so you can't call it from the app.
   struct item {
      atomic_counter<int>& counter;
      const char* caption;
      };
   vararray_s<item> counter_list;
      // public, so you can write your own code to iterate over this list.
   int register (atomic_counter<int>& counter, const char* caption);
      // register always returns 0, but it's not void so it may be used in an expression.  That's
      // handy to get it called for a static global counter.
   void DebugString_stats (bool all=false /* just the non-zero values */);
   ~debug_object_count_t() { DebugString_stats(); }
      // warnings are printed when my singleton goes out of scope, e.g. at program termination.
   };

extern debug_object_count_t debug_object_count;  // a singleton


/*    The Idea
Use a static counter in a class to make sure all instances are destroyed.
Use this class to automatically report this condition, and provide a central
list for your own debugging code.

E.g.

   atomic_counter<int> Foo::instance_count;  // static member
   static int dummy= debug_object_count.register (Foo::instance_count, "Foo's counter");

The global dummy exists to get its initializer called, so register can be called during the
static constructor stage.

Bug you can also write:

   atomic_counter<int> Foo::instance_count= debug_object_count.register (instance_count, "Foo's counter");

which avoids the dummy and any issues of accessing a private instance_count.

Note too that you don't have to register the counter this early.  Any time before program termination
will do, to get the warning at shut-down.  If you put in other debug statements during debugging, though,
you will obviously have to get them registered before they will show up on the report.

*/

