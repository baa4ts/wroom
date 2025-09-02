# Hook para ocultar procesos en Windows

## 📝 Lógica simple

1. Se recorre la lista de procesos (`SystemInformation`).
2. Si el **primer proceso** está en la lista de ocultar, se busca el **primer proceso válido** y se usa como inicio de la lista.
3. Para cada proceso siguiente:

   * Si está en la lista de ocultar, se **ajusta `NextEntryOffset` del proceso anterior** para saltarlo.
   * Si no está en la lista de ocultar, se actualiza el **último proceso visible** (`pAnterior`).
4. Se repite hasta el final de la lista.

> Funciona para ocultar **varios procesos** a la vez.

---

## 🔹 Ejemplo conceptual

Lista original:

```
[System] -> [Brave] -> [Notepad] -> [Chrome] -> NULL
```

Lista final ocultando `Brave` y `Chrome`:

```
[System] -> [Notepad] -> NULL
```

* Los offsets se ajustan para saltar los procesos ocultos.

---

## 💻 Compilación

* **Runtime estático:** `/MT`
* **Gestor de dependencias:** [vcpkg](https://github.com/microsoft/vcpkg)
* **Hooking de API:** `Detours`

  * Instalar con vcpkg:

    ```bash
    vcpkg install detours
    ```
