📄 Homework 2 – Zombie Processes Project

Autor: Iván Ramos de la Torre Curso: Ingeniería de Software y Minería de Datos

Descripción del Proyecto

Este proyecto tiene como objetivo la práctica y comprensión de procesos zombie y su manejo en Linux.

Se implementa:

    Creación de procesos zombie (zombie_creator)

    Detección de procesos zombie (zombie_detector)

    Estrategias de reapado de zombies (zombie_reaper)

    Daemon de largo tiempo sin generar zombies (process_daemon)

    Librería de prevención de zombies (libzombie.a)

Estructura del Proyecto

homework2/
├── src/
│ ├── zombie_creator.c    # Parte 1: Crear zombies
│ ├── zombie_detector.c   # Parte 2: Detectar zombies
│ ├── zombie_reaper.c     # Parte 3: Reapado de zombies
│ ├── process_daemon.c    # Parte 4: Daemon de largo tiempo
│ ├── zombie.c            # Parte 5: Librería zombie
│ └── zombie.h            # Parte 5: Header de librería
├── tests/
│ ├── test_creator.sh     # Script de prueba Parte 1
│ ├── test_detector.sh    # Script de prueba Parte 2
│ ├── test_reaper.sh      # Script de prueba Parte 3
│ └── test_daemon.sh      # Script de prueba Parte 4
├── Makefile              # Compilación de todo
├── README.md             # Documentación
└── DEMO.md               # Evidencia de tests (opcional)

Compilación

    Abrir terminal en homework2/

    Ejecutar:

	Make

Esto compilará todos los programas y generará la librería libzombie.a.

Ejecutables

    zombie_creator → Crea N procesos zombie

    zombie_detector → Detecta procesos zombie en el sistema

    zombie_reaper → Demuestra tres estrategias de reapado de zombies

    process_daemon → Daemon de largo tiempo que nunca genera zombies

    test_lib → Ejemplo de uso de la librería libzombie.a

Uso de cada parte

1️⃣ Zombie Creator

Bash

./zombie_creator <num_zombies>

    Crea <num_zombies> zombies.

    Mantiene al proceso padre vivo hasta presionar Enter.

2️⃣ Zombie Detector

Bash

./zombie_detector

    Escanea /proc en busca de procesos zombies.

    Imprime un reporte con PID, PPID, comando y estado.

3️⃣ Zombie Reaper

Bash

./zombie_reaper <strategy>

Strategy	Descripción
waitpid	Reapado explícito con waitpid()
sigchld_handler	Manejo automático con SIGCHLD
sigchld_ignore	Ignorar SIGCHLD para reapado automático (con init)

    Crea 10 hijos y los reapa según la estrategia seleccionada.

4️⃣ Process Daemon

Bash

./process_daemon &

    Se ejecuta como demonio.

    Crea trabajadores cada 5 segundos.

    Nunca deja zombies (usa SIGCHLD).

    Log en /tmp/daemon.log.

    Detener con: killall process_daemon

5️⃣ Librería Zombie (libzombie.a)

Función	Uso
zombie_init();	Inicializar la librería (configura el manejador de SIGCHLD).
pid_t pid = zombie_safe_fork();	Crear procesos seguros, evitando zombies.
char *args[] = {"sleep", "2", NULL}; zombie_safe_spawn("sleep", args);	Ejecutar comandos con prevención de zombies.
zombie_stats_t stats; zombie_get_stats(&stats);	Obtener estadísticas de los procesos seguros creados.

Tests

Los scripts de prueba se encuentran en tests/:
Bash

chmod +x tests/*.sh
./tests/test_creator.sh
./tests/test_detector.sh
./tests/test_reaper.sh
./tests/test_daemon.sh

Valida que los programas funcionen correctamente y que no queden procesos zombies después de reaparlos o al correr el daemon.

Limpieza

Bash

make clean

Elimina ejecutables y archivos objeto generados.

Notas

    Ejecutar los tests y programas desde la carpeta homework2/ para que las rutas relativas funcionen correctamente.

    Requiere Linux con soporte /proc y fork().

    Los programas están comentados para explicar cada función y paso.
