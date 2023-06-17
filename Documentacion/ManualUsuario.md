##### Universidad de San Carlos de Guatemala
##### Escuela de Ingeniería en Ciencias y Sistemas - Facultad de Ingeniería
##### Arquitectura de Computadoras y Ensambladores 1, 1er. Semestre 2023

##### Integrantes:
- 201902502 - Carlos Eduardo Soto Marroquín
- 201709282 - Carlos Javier Martinez Polanco
- 201807032 - Douglas Alexander Soch Catalán
- 201945242 - Jefferson Gamaliel Molina Barrios
- 201807389 - Gladys Leticia Ajuchán Vicente

# MANUAL PARA EL USUARIO
### Sistema de Cargado de Celulares
##### Contenido
- Sistema de Cargado de Delulares
- Requisitos del sistema
- Interfaz
- Datos Cifrados
- Secuencia Inicial
- Menú principal
- Registro 
- Inicio de sesión
- Menú de Usuarios
- Ingreso y retiro de celular
- Cerrar sesión
- Eliminación de cuenta
- Menú de administrador
- Registro de Eventos o Logs
- Estados del Sistema

### Sistema de Cargado de Delulares
El siguiente prototipo es un sistema de cargado de celulares en el que los usuarios registrados podrán obtener acceso temporal a un espacio para la carga de su dispositivo. Se le brindará a los administradores herramientas para controlar de forma efectiva el sistema y obtener datos relevantes. Es preciso, también, considerar aspectos como la seguridad en un sistema como este; por lo que se deberán implementar características que la permitan. Específicamente se solicita la implementación de un prototipo simulado y otro físico. El prototipo simulado será el principal, en este estarán desplegadas las funcionalidades más importantes. El físico servirá como principio para la eventual implementación física del sistema.

### Requisitos del sistema
###### Procesador:
- Intel Superior a la 4ta gen
- AMD Superior a las versiones de Opteron
###### Memoria RAM:
- Superior a las 2GB de RAM, en versiones superiores a DDR3
###### Espacio de Disco:
- Tener libre 30MB
###### Sistema Operativo:
- MacOS, Windows, Distribuciones de Linux (Compatibles con Proteus 8.12).
###### Herramientas de desarrollo de Software:
- Arduino IDE y Proteus 8.12
###### Resolución Gráfica:
No es necesario una tarjeta gráfica o un chip de video adicional para ejecutar el prototipo del sistema.

### Interfaz
El sistema cuenta con dos interfaces con las que el usuario podrá interactuar con el Sistema de Cargado de Celulares para su uso o para su configuración.

- Elementos:

1. Panel de operación:
Se mostrará una matriz de LEDs que mostrará la variación de letras y signos válidos dentro del sistema que permitirá ingresar los datos alfanuméricos al sistema. 
Seguidamente se encuentra una pantalla LCD e inmediatamente un teclado matricial de 3x4 teclas que permitirá ingresar los datos numéricos al sistema. 
Por ultimo se encuentran situados dos botones, seguidamente del teclado, el primero que se llamará ***ACEPTAR*** y el siguiente ***CANCELAR*** Su ejecución será de distinta forma dependiendo lo que se encuentre realizando el para ese momento.

2. Celulares:
Como usuario registrado, es posible tener más de un dispositivo dentro del sistema, la única condición que existe para poder ingresar uno nuevo es que hayan espacios disponibles. Para un nuevo ingreso el sistema elegirá automáticamente el primer compartimento vacío que encuentre y sera ese el que usará el usuario.

3. Registro y autenticación:
Las entradas para esta parte podrán ser ingresadas por medio de la aplicación móvil, así como también por el panel de operación del sistema. Se solitará:

|   NOMBRE    | NUMERO DE CELULAR |              CONTRASEÑA                        |
|-------------|-------------------|------------------------------------------------|
|Letras de A-Z|Números de 0-9     |Letras de A-Z, números de 0-9 y caracteres *#$! | 

4. Roles
El sistema considerá una serie de roles y dependiendo de este un usuario tendrá acceso a una gama de funcionalidades específicas. Habrán dos roles distintos en este sistema:
Administrador y usuario. 
El usuario administrador tendrá acceso a funcionalidades de control y gestión del sistema.
Los usuarios podrán ingresar y retirar celulares.

5. Credenciales: 
Existen dos timpos de usuarios: **"Administrador"**. Las credenciales del administrador serán las siguientes:

|    NOMBRE   | CONTRASEÑA |
|-------------|------------|
| ADMIN*22922 | GRUPO18    |


### Datos cifrados
Por motivos de seguridad se deberán obfuscar tales datos mediante un cifrado aplincado dos veces y cuyas llaves deberán ser elegidas por medio de las siguientes reglas:
- Teniendo los carnés de sus integrantes ordenados de forma ascendente la primera llave será el último caracter del carné mayor.
- Y la segunda será el penúltimo caracter del carné más pequeño.
- Si con las reglas anteriores se toman dos llaves iguales se deberá elegir el antepenúltimo caracter y avanzar así hasta tener dos llaves distintas.

### Registro 
Se podrá registrar un nuevo usuario en el sistema. De manera secuencia, se le solicitará al usuario que ingrese, por aplicación o por panel de operación, cada campo requerido.

### Inicio de sesión
El usuario o administrador podrá ingresar al sistema y realizar sus gestiones. Se le solicitará al usuario su nombre y contraseña. El sistema verificará los datos. De ser correctos se le dará acceso al menú que le corresponda al usuario. De lo contrario se le dará una oportunidad más. Si el usuario llegase a fallar nuevamente el sistema se bloqueará por 10 segundos y volverá a la secuencia inicial pasado ese tiempo.

![Descripción de la imagen](/Img/1.png "Inicio")
![Descripción de la imagen](/Img/2.png "Menu de operaciones")
### Menú de Usuarios
Al iniciar sesión se presentará en la pantalla LCD del panel de operación un menú que tendrá opciones para: 
- ingreso de celulares
- retiro de los mismos
- cerrar sesión 
- eliminación de su cuenta


### Ingreso y retiro de celular
Cuando el usuario se encuentre regitrado podrá tener más de un discpositivo dentro del sistema, la única condición que existe para poder ingresar uno nuevo es que hayan espacios disponibles.
Para un nuevo ingreso el sistema elegirá automáticamente el primer compartimento vacío que encuentre y sera ese el que usará el usuario. 

![Descripción de la imagen](/img/3.png "Ingreso y retiro de celular")

### Cerrar sesión
El usuario podrá cerrar su sesión por medio de esta opción o, automáticamente, la sesión se cerrará luego de 5 minutos de inactividad. 

![Descripción de la imagen](/img/4.png "Cerrar sesión")

### Eliminación de cuenta
Con esta opción el usuario podrá darse de baja del sistema. De ser ese el caso, luego de
evaluar la situación el sistema redirigirá al usuario al menú de retiro de celular para proceder con un retiro.

### Menú de administrador
El administrador, una vez iniciada su sesión, verá un menú que tendrá entre sus opciones: 
- visualización de logs
- verificación del estado del sistema

### Registro de Eventos o Logs
Toda acción de importancia que ocurra en el sistema se registra junto a una descripción. 
Los eventos que se deberán insertar en la memoria son:

- Login success
- Login success
- Attemp log error
- Sesion closed
- Delete error
- Delete success
- Entry cel. error
- Entry success
- Out cel. error

### Estados del Sistema
El administrador podrá consultar una serie de datos relevantes al sistema. Antes de ingresar a esta sección se deberá asegurar una conexión Bluetooth con un dispositivo con la aplicación móvil. Una vez hecho esto, se podrá proceder a mostrar los datos solicitados en la
pantalla LCD, de forma secuencial, y en la aplicación móvil. 

![Descripción de la imagen](/img/6.jpeg "Estados del Sistema")
![Descripción de la imagen](/img/5.png "Estados del Sistema")