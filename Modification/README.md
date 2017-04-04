# Algoritmos y Estructuras de Datos Avanzadas

## Práctica 3: Implementación de búsqueda mediante Tabla Hash (modificación)

### Objetivo

Desarrollar un tipo de dato genérico en lenguaje C++ que implemente la técnica de búsqueda basada en tabla hash con dispersión cerrada.

Realizar un análisis del rendimiento de la tabla hash con distintas funciones de dispersión, distintas estrategias de exploración y distintos factores de carga. En este análisis se incluye el estudio del comportamiento para las funciones de dispersión: módulo, suma y pseudo-aleatoria; y para las estrategias de exploración: lineal, cuadrática, dispersión doble y re-dispersión.

Para realizar el estudio del comportamiento de la tabla hash se utilizarán valores de clave del tipo *Matricula*, que representa las matrículas de los vehículos a motor. Un valor del tipo *Matricula* está formado por la concatenación de cuatro dígitos numéricos y tres letras. Los posibles valores están en el rango [0000AAA...9999ZZZ]. Además, como modificación, el tipo *Matricula* podrá tomar valores formados por la concatenación de dos letras, cuatro dígitos numéricos y otras dos letras. Los posibles valores adicionales están en el rango [AA0000AA...ZZ9999ZZ].

### Compilación y ejecución

El ejecutable generado se guarda en *bin/*

~~~
    make
~~~

### Información personal

**Autor:** [Kevin Estévez Expósito](https://alu0100821390.github.io/)

**ULL-ID:** alu0100821390
