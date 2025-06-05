# Dependency Troubleshooting Guide

## 🚨 **Common Loading Issues**

### **Error: "找不到指定的模块" (The specified module could not be found)**

**Error Code**: `0x0000007E`  
**Meaning**: DLL dependency loading failure

## 🔧 **Solutions**

### **1. Install Visual C++ Redistributables**

**Download and install the latest Visual C++ Redistributables:**
- [Microsoft Visual C++ Redistributable for Visual Studio 2022 (x64)](https://aka.ms/vs/17/release/vc_redist.x64.exe)

**Why needed**: The plugin requires Visual C++ runtime libraries that may not be installed on the server.

### **2. Verify LeviLamina Version**

**Check LeviLamina version compatibility:**
```bash
# Ensure you're running LeviLamina 3 v1.2.0 or later
./bedrock_server_mod.exe --version
```

**Required**: LeviLamina >= 1.2.0

### **3. Check Plugin Architecture**

**Verify the plugin is built for the correct architecture:**
- **Server Architecture**: x64 (64-bit)
- **Plugin Architecture**: Must match (x64)

**Check with:**
```bash
file potato-bonemeal-blocker.dll
# Should show: PE32+ executable (DLL) (console) x86-64
```

### **4. Dependency Analysis Tools**

**Use Dependency Walker or similar tools to check missing dependencies:**

1. **Download Dependency Walker**: http://www.dependencywalker.com/
2. **Open the plugin DLL**: `potato-bonemeal-blocker.dll`
3. **Check for missing dependencies** (shown in red)

**Common missing dependencies:**
- `MSVCP140.dll` - Visual C++ runtime
- `VCRUNTIME140.dll` - Visual C++ runtime
- `api-ms-win-*.dll` - Windows API sets

### **5. Plugin Installation Steps**

**Correct installation procedure:**

1. **Stop the server**
2. **Copy the plugin DLL** to `plugins/` directory
3. **Ensure manifest.json** is in the same directory or properly configured
4. **Start the server**
5. **Check logs** for loading confirmation

### **6. Debug Mode Installation**

**For debugging, try debug mode:**

1. **Build in debug mode**:
   ```bash
   xmake f -m debug
   xmake
   ```

2. **Install debug version** and check for more detailed error messages

### **7. Manual Dependency Check**

**Check if required DLLs are accessible:**

```bash
# Check if LeviLamina DLLs are in PATH or same directory
dir LeviLamina.dll
dir bedrock_runtime.dll

# Check system PATH includes LeviLamina directory
echo %PATH%
```

## 🛠️ **Build Configuration Fixes**

### **Applied Fixes in Latest Version**

1. **Explicit Runtime Library Linking**:
   ```lua
   add_syslinks("kernel32", "user32", "gdi32", "winspool", "shell32", "ole32", "oleaut32", "uuid", "comdlg32", "advapi32")
   ```

2. **Proper Runtime Configuration**:
   ```lua
   set_runtimes("MD")  -- Multi-threaded DLL runtime
   ```

3. **Delay Loading**:
   ```lua
   add_ldflags("/DELAYLOAD:bedrock_runtime.dll")
   ```

4. **Explicit Exports**:
   ```lua
   add_ldflags("/EXPORT:ll_plugin_load")
   add_ldflags("/EXPORT:ll_plugin_unload")
   ```

5. **Module Definition File**:
   ```
   EXPORTS
   ll_plugin_load
   ll_plugin_unload
   ```

## ✅ **Verification Steps**

### **1. Check Plugin Loading**

**Look for these log messages:**
```
INFO [LeviLamina] 正在加载 PotatoBoneMealBlocker v1.1.0
INFO [PotatoBoneMealBlocker] Loading Potato Bone Meal Blocker v1.1.0...
INFO [PotatoBoneMealBlocker] Compatible with LeviLamina 3 v1.2.0
INFO [PotatoBoneMealBlocker] Potato Bone Meal Blocker enabled successfully!
```

### **2. Test Functionality**

**In-game testing:**
1. **Get bone meal** and **potato crops**
2. **Try to use bone meal on potatoes** - should be blocked
3. **Try to use bone meal on wheat/carrots** - should work
4. **Check for blocking message**: "§cBone meal cannot be used on potato crops!"

### **3. Check Statistics**

**Plugin should track blocked attempts:**
- Counter increments when bone meal is blocked
- Logs show blocked attempts with player names and positions

## 🆘 **If Issues Persist**

### **1. Collect Debug Information**

```bash
# Check server logs
tail -f logs/latest.log

# Check Windows Event Viewer
eventvwr.msc
# Look in: Windows Logs > Application
```

### **2. Try Minimal Configuration**

1. **Remove other plugins** temporarily
2. **Test with just this plugin**
3. **Check if loading succeeds**

### **3. Contact Support**

**Provide this information:**
- LeviLamina version
- Windows version
- Plugin version
- Complete error logs
- Dependency Walker output (if available)

---

**Most dependency issues are resolved by installing the Visual C++ Redistributables and ensuring proper LeviLamina version compatibility.**
