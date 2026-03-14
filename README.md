# Traffic Light Log - Sistema de Monitoramento de Tráfego

## 📋 Descrição

Sistema em C++ para armazenar e consultar registros de veículos capturados por uma câmera de trânsito instalada em um semáforo. O sistema permite registrar placas de veículos com timestamp e realizar consultas por intervalo de tempo.

## 🗂️ Estrutura do Projeto

```
traffic-light-log/
├── traffic_light_log.h      # Declarações da classe e struct Entry
├── traffic_light_log.cpp    # Implementação dos métodos
├── main.cpp                 # Programa de demonstração
└── README.md                # Este arquivo
```

## 🛠️ Requisitos

- **Compilador C++**: g++ (GCC) ou clang++
- **Padrão C++**: C++17 ou superior
- **Sistema Operacional**: Linux, macOS, ou Windows (com MinGW/WSL)

### Verificar se você tem o g++ instalado:

```bash
g++ --version
```

Se não tiver, instale:
- **Ubuntu/Debian**: `sudo apt-get install g++`
- **macOS**: `xcode-select --install`
- **Windows**: Instale MinGW ou use WSL

## 🚀 Compilação

### Método 1: Compilação Simples (Recomendado)

```bash
g++ -std=c++17 -Wall -Wextra main.cpp traffic_light_log.cpp -o traffic_log
```

**Explicação dos flags:**
- `-std=c++17`: Usa o padrão C++17
- `-Wall`: Habilita warnings importantes
- `-Wextra`: Habilita warnings adicionais
- `-o traffic_log`: Nome do executável gerado

### Método 2: Compilação Separada (Projetos Maiores)

```bash
# Compila cada arquivo .cpp em arquivo objeto (.o)
g++ -std=c++17 -Wall -c traffic_light_log.cpp -o traffic_light_log.o
g++ -std=c++17 -Wall -c main.cpp -o main.o

# Linka os arquivos objetos
g++ traffic_light_log.o main.o -o traffic_log
```

### Método 3: Com Otimização (Release)

```bash
g++ -std=c++17 -O2 -Wall main.cpp traffic_light_log.cpp -o traffic_log
```

**Flag adicional:**
- `-O2`: Otimização de performance

### Método 4: Debug Mode

```bash
g++ -std=c++17 -g -Wall main.cpp traffic_light_log.cpp -o traffic_log_debug
```

**Flag adicional:**
- `-g`: Inclui símbolos de debug para usar com gdb

## ▶️ Executando o Programa

### Linux / macOS:

```bash
./traffic_log
```

### Windows (MinGW / CMD):

```cmd
traffic_log.exe
```

## 📦 Limpando Arquivos Compilados

```bash
# Linux / macOS
rm -f traffic_log traffic_log_debug *.o

# Windows (CMD)
del traffic_log.exe traffic_log_debug.exe *.o
```

## 🧪 Exemplo de Uso

```cpp
#include "traffic_light_log.h"
#include <iostream>

int main() {
    // Criar instância do log
    TrafficLightLog log;
    
    // Adicionar entrada
    auto now = std::chrono::system_clock::now();
    Entry entry("ABC-1234", now);
    log.addEntry(entry);
    
    // Consultar entradas em intervalo
    auto start = now - std::chrono::hours(1);
    auto end = now + std::chrono::hours(1);
    auto results = log.getEntriesInRange(start, end);
    
    // Exibir resultados
    std::cout << "Entradas encontradas: " << results.size() << "\n";
    
    return 0;
}
```

## 📚 API Principal

### Struct Entry

```cpp
struct Entry {
    std::string license_plate;
    std::chrono::system_clock::time_point timestamp;
    
    Entry(const std::string& plate, 
          const std::chrono::system_clock::time_point& time);
};
```

### Classe TrafficLightLog

#### Métodos Principais:

- **`void addEntry(const Entry& entry)`**
  - Armazena uma nova entrada de veículo
  
- **`std::vector<Entry> getEntriesInRange(start, end)`**
  - Retorna todas as entradas em um intervalo de tempo

#### Métodos Auxiliares:

- **`size_t getEntryCount() const`**
  - Retorna o número total de entradas armazenadas
  
- **`void clear()`**
  - Remove todas as entradas do log
  
- **`bool isEmpty() const`**
  - Verifica se o log está vazio

## 🔧 Troubleshooting

### Erro: "g++ not found"
**Solução**: Instale o compilador g++ conforme instruções na seção Requisitos

### Erro: "undefined reference to..."
**Solução**: Certifique-se de compilar TODOS os arquivos .cpp juntos:
```bash
g++ -std=c++17 main.cpp traffic_light_log.cpp -o traffic_log
```

### Erro: "no such file or directory: traffic_light_log.h"
**Solução**: Certifique-se de que todos os arquivos estão no mesmo diretório

### Warning: "unused variable"
**Solução**: Remova variáveis não utilizadas ou use-as no código

## 📝 Notas de Desenvolvimento

- Usa STL (Standard Template Library) do C++
- Armazenamento em memória (sem banco de dados)
- Value semantics para struct Entry
- Constness apropriado para métodos read-only

## 🎯 Melhorias Futuras Possíveis

- [ ] Validação de formato de placa
- [ ] Ordenação automática por timestamp
- [ ] Busca binária para queries mais eficientes
- [ ] Persistência em arquivo (serialização)
- [ ] Thread-safety com mutexes
- [ ] Suporte a múltiplas câmeras
- [ ] Estatísticas de tráfego

## 👤 Autor

Desenvolvido como parte de teste técnico para vaga de desenvolvedor.

## 📄 Licença

Este projeto é de código aberto e está disponível para uso educacional.

---

**Data de criação**: 2026-03-11