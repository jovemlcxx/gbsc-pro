<p align="center">
    <img alt="gbsc-pro" src="assets/gbsc-pro%20logo.png" />
</p>

---

Firmware do **GBSC Pro** em **português do Brasil**, desenvolvido para a comunidade brasileira.

Converte o vídeo de consoles retrô para HDMI até 1080p, com baixa latência, quadro 4:3 centralizado, scanlines prontas para uso e menus em **PT-BR e EN-US** (OLED, TV e Web).

Baseado no [brisma/gbsc-pro](https://github.com/brisma/gbsc-pro), que deriva do [RetroScaler/gbsc-pro](https://github.com/RetroScaler/gbsc-pro) e do [gbs-control](https://github.com/ramapcsx2/gbs-control) de ramapcsx2.

## Links

[Documentação](docs/DOCUMENTACAO.md) | [Manual do GBSC Pro](https://www.retroscaler.com/?page_id=480) | [Discord](https://discord.com/invite/2MMWRkVRbk)

## Scanlines

As scanlines são o principal destaque deste firmware: **já vêm ligadas e configuradas**. Ao ligar a GBS, elas estão ativas.

- **Geradas pelo próprio chip:** o TV5725 escurece as linhas da imagem antes de escalar. Não há camada sobreposta nem perda de nitidez.
- **Configuração de fábrica:** ligadas, intensidade 00 (a mais escura), com Filtro de Linha e Nitidez ativos.
- **Sempre ajustáveis:** liga/desliga e intensidade (00 a 50) pelo menu da TV, menu OLED, controle remoto e Web. O valor é guardado mesmo quando o sinal atual não permite scanlines.
- **Disponíveis em RGB pela SCART:** no firmware original elas ficavam bloqueadas ao ligar neste modo. Agora funcionam.
- **Persistentes:** trocar de preset, mudar a resolução ou reiniciar mantém a sua configuração.
- **Compatíveis com a escala:** funcionam com o quadro 4:3 e com o mover e esticar de ~1 pixel.

| Saída | Fator vertical (240p) | Scanlines |
|---|---|---|
| 1280x960 | 4× | Perfeitas |
| 1280x720 | 3× | Regulares |
| 1920x1080 | 4,5× | Regulares |

Fontes atendidas: 240p/288p, ou 480i/576i com deinterlace *Bob*.

## Novidades

### Idioma
- **PT-BR e EN-US** em todo o sistema: menu OLED, menu da TV e Web.
- Troca em *Menu → página 4 → Idioma*, ou na Web em *Settings → Idioma*. O padrão é PT-BR.

### Imagem
- **Quadro 4:3 fixo e centralizado** em todas as resoluções. A área 4:3 é o limite: o que passar dela é cortado.
- **Mover e esticar com passos de ~1 pixel.** O esticar horizontal cresce para a direita e o vertical para baixo.
- **Centralizar** (mantém o tamanho) e **Redefinir escala** (volta ao ajuste automático), no menu *Ajustes de Tela*, na Web e pela tecla INFO do controle.
- Saída padrão em 1080p, com cores corretas.

### Menus
- Menus reformulados e traduzidos por completo, com o mesmo layout do inglês na TV.
- Resoluções ordenadas da maior para a menor em todas as telas.

## Padrões de fábrica

Tudo isto já vem ativo em uma GBS nova ou depois de *Restaurar Padroes*, sem precisar configurar.

| Item | Firmware do brisma | Este firmware |
|---|---|---|
| Idioma | Inglês | **PT-BR** (EN-US selecionável) |
| Resolução de saída | 1280x960 | **1920x1080** |
| Quadro 4:3 | Não existe | **Ligado**, fixo e centralizado |
| Scanlines | Desligadas | **Ligadas** |
| Intensidade das scanlines | 30 | **00** (a mais escura) |
| Scanlines em RGB/HV (SCART) | Bloqueadas | **Liberadas** |
| Filtro de Linha | Desligado | **Ligado** |
| Nitidez | Desligada, zerada a cada preset | **Ligada**, salva e reaplicada |
| Pixels duros (filtro de 6 taps desviado) | Desligado | **Ligado** |
| Active FrameTime Lock | Desligado | **Ligado** |
| HDMI Limited Range | Ligado | **Desligado** |
| Tema do menu da TV | Clássico | **Escuro** |
| Volume | 38 | **35** |
| Reaplicação do preset ao ligar | Não existe | **Automática** |
| Passo de mover e esticar | Grosso | **~1 pixel** |
| Ordem das resoluções | Misturada | **Da maior para a menor** |
| Menus | Originais | **Reformulados** |

Permanecem como no original: Peaking e Resposta de Cor ligados, Altura Total ligada, Deinterlace Adaptativo, entrada RGBs e *Matched Presets* ligado.

Na primeira inicialização depois de gravar, o firmware aplica esses padrões **uma única vez** às preferências e aos slots já salvos. Depois disso, tudo continua configurável normalmente.

## Melhorias e correções em relação ao firmware do brisma

### Ao ligar
- **Configurações sobrescritas:** trocar de preset ou reiniciar substituía os filtros em uso (scanlines, intensidade, filtro de linha, peaking, resposta de cor) pelos do slot. Agora os filtros em uso são mantidos.
- **Scanlines bloqueadas:** com RGB pela SCART, a GBS entra no modo RGB/HV e as scanlines ficavam travadas (vermelho) até redefinir tudo. Agora funcionam.
- **Nitidez perdida:** era zerada a cada troca de preset, inclusive ao ligar. Agora é salva e reaplicada.
- **Borda cinza:** o conversor HDMI travava no primeiro timing. O firmware reaplica o preset uma vez, automaticamente, depois que o sinal estabiliza.
- **Padrões de fábrica:** aplicados de fato nas configurações já salvas, sem reconfigurar.
- **Tearing:** o Active FrameTime Lock vem ligado e elimina a linha de tearing parada.
- **Preto no 1080p:** o HDMI Limited Range vem desligado.
- **Calibração do ADC:** corrigido um bug herdado do gbs-control em que uma intensidade de scanline inválida desligava a calibração.

### Imagem e escala
- **Mover e esticar:** a imagem só crescia para um lado e o quadro visível aumentava junto, ultrapassando o 4:3. Agora o quadro é fixo, corta o excesso e cada toque move ~1 pixel.
- **Controle do menu:** direita estreitava e cima achatava, o contrário da Web. Agora as direções são iguais.
- **Escala salva:** é reaplicada centralizada ao religar.
- **Bordas do 1080p:** eliminadas as faixas verdes nas laterais.
- **Atalhos de scanline:** guardam o valor mesmo quando o sinal atual não permite scanlines.

### Menus
- **Idioma** como item de menu, com tradução completa e sem abreviações.
- **Menu da TV:** o tracejado começa logo após o rótulo, os valores ficam alinhados à direita e nenhum rótulo encosta no valor.
- **Rótulo corrigido:** "EnableFrameTimeLock" na verdade liga o gerador de clock externo, e passou a se chamar *Gerador de Clock*.
- **Menu principal da TV** sem a seta repetida à direita do item selecionado.

## Como instalar

1. Baixe os arquivos da pasta [`releases/`](releases/).
2. Abra o `NodeMCU-PyFlasher.exe` (ou o [gbsc-pro-flasher](gbsc-pro-flasher/)) e grave `firmware-gbsc-pro-by-jovemlcxx.bin` **somente no ESP8266**.
3. Mantenha **Erase flash: no** para preservar o WiFi e os presets.
4. O módulo AV (`GBSC_PRO_AVMODULE_v2.4.1.bin`, com o `GBSC_PRO_Programmer.exe`) só precisa ser gravado se ainda não estiver instalado.

Antes de gravar, guarde uma cópia do firmware atual para poder voltar atrás.

### Configuração da TV
Em **1280x960 e 1280x1024**, ajuste a TV para **nível de preto Baixo / faixa HDMI Limitada**. Detalhes na [documentação](docs/DOCUMENTACAO.md).

## Estrutura do repositório

| Pasta | Conteúdo |
|---|---|
| [firmware/](firmware/) | Código-fonte do ESP8266 (TV5725, OSD, menu OLED, Web UI) |
| [gbsc-pro-flasher/](gbsc-pro-flasher/) | Ferramenta de gravação (Windows, macOS e Linux) |
| [releases/](releases/) | Firmware, módulo AV e ferramentas de gravação (Windows) |
| [docs/](docs/) | Documentação |
| [assets/](assets/) | Imagens |

O firmware do módulo AV (HC32), o ADV Manager e os arquivos de hardware (PCB, BOM) não foram modificados e estão no repositório original: [brisma/gbsc-pro](https://github.com/brisma/gbsc-pro).

## Compilar

```bash
# Firmware do ESP8266 (PlatformIO)
cd firmware && python -m platformio run

# Web UI (somente se alterar a interface)
cd firmware/public && npm install && npx tsc ./src/index.ts --target ES6 && cd scripts && node ./build.js && bash ./html2h.sh
```

O binário é gerado em `firmware/.pio/build/gbsc-pro/firmware.bin`.

## Agradecimentos

- [@brisma](https://github.com/brisma) pelo [gbsc-pro](https://github.com/brisma/gbsc-pro), base deste firmware
- [RetroScaler](https://github.com/RetroScaler/gbsc-pro) pelo GBSC Pro
- [@ramapcsx2](https://github.com/ramapcsx2) pelo [gbs-control](https://github.com/ramapcsx2/gbs-control)

## Licença

GPL-3.0, herdada do gbs-control. Partes do brisma/gbsc-pro são MIT, com copyright de Brisma.
