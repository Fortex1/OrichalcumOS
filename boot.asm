[BITS 32]

global start

start:
    ; Вимкнення переривань
    cli

    ; Завантаження адреси ядра
    mov esp, 0x90000     ; Встановлення стеку
    jmp 0x1000           ; Перехід до ядра

times 510-($-$$) db 0    ; Заповнення сектору до 510 байтів
dw 0xAA55                ; Завантажувальний підпис