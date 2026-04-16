extern "C" void KernelMain() { // To prevernt name mangling and to make it callable from assembly, we declare the function as extern "C".
    while (1) __asm__("hlt");
}
