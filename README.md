# ConfigLib
Simple text config file reader/writer. This is a single file header-only library, so it is easy to add to any C++ project with just an include statement (a la Boost). No complicated library installs or linking needed.

Bash-style comments are supported. C-style multi-line comments are also partially supported.

Create a simple config file with key=value type entries. Both key and value are treated as string types.
<pre>
# Number of clusters: integer or auto
Nc=auto
# Number of probes: 5 or 9 or odd number or auto
num_probes=auto # auto detect
# Mode: PLN or SFS or TWOSTAGEFS
  mode = PLN    # clean
# fs_method: SFS or PLOFS
fs_method=PLOFS
# Allow PLN with only a single cluster
g_singleton_disallowed=FALSE
/* A multi-
line
comment using C style
CATCH:
1. / * and * / must be at the beginning of the line.
2. No nesting allowed.
*/
</pre>

The libray is used simply by:

```cpp
#include "ConfigLib.hpp"

using namespace std;

int main() {
    
    // Read an existing settings file
    ConfigLib conf("settings_final.txt");
    cout<<conf.get("Nc")<<endl;
    cout<<conf.get("num_probes")<<endl;
    int Nc = ConfigLib::string2int(conf.get("Nc"));
    
    // Write a config
    ConfigLib conf2("settings.txt");
    conf2.put("car", "maruti");
    conf2.put("house", "clean");
    conf2.write();
    // conf.overwrite("settings_final.txt");

    return 0;
}
```

