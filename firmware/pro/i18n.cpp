// ====================================================================================
// i18n.cpp
// UI translation table (en-US -> pt-BR) and language persistence. See i18n.h.
//
// OSD rules (TV): text is drawn on a fixed 28-column grid and many rows have value
// columns / dash runs hard-coded after the English label length. Keep pt-BR text no
// longer than the English one where possible (OSD_writeStringAtRow pads shorter text
// with spaces, and OSD_drawDashRange pushes dashes right when a label is longer).
// Keep leading dashes of right-aligned values ("---Dark") in the key AND the value.
// ====================================================================================

#include "i18n.h"
#include <LittleFS.h>
#include <string.h>
#include "../OLEDMenuTranslations.h"
#include "../OLEDMenuTranslations_pt.h"

uint8_t uiLang = LANG_PT;

// X("English", "Portugues")
#define I18N_TABLE \
    /* ---- main menu (OLED + TV) ---- */ \
    X("Input source", "Fonte de Entrada") \
    X("AV/SV Inputs", "Entradas AV/SV") \
    X("AV/SV settings", "Ajustes de AV/SV") \
    X("Output Resolution", "Resolucao") \
    X("Output resolution", "Resolucao de Saida") \
    X("Screen Settings", "Ajustes de Tela") \
    X("Screen settings", "Ajustes de Tela") \
    X("Picture Settings", "Imagem") \
    X("Picture settings", "Ajustes de Imagem") \
    X("System Settings", "Sistema") \
    X("System settings", "Ajustes do Sistema") \
    X("Preferences", "Preferencias") \
    X("Developer", "Desenvolvedor") \
    X("Firmware Version", "Firmware") \
    X("Firmware version", "Versao do Firmware") \
    X("Firmware", "Firmware") \
    X("Version", "Versao") \
    X("Factory Reset", "Restaurar Tudo") \
    X("Factory reset", "Restaurar Padroes") \
    X("Factory", "Restaurar") \
    X("Reset?", "Padroes?") \
    X("Restart", "Reiniciar") \
    X("Language", "Idioma") \
    X("Reset all settings to", "Restaurar todos os ajustes") \
    X("factory defaults", "para o padrao de fabrica") \
    X("Yes", "Sim") \
    X(" Yes", " Sim") \
    X("No", "Nao") \
    X(" No", " Nao") \
    /* ---- OLED titles ---- */ \
    X("Menu->System", "Menu->Sistema") \
    X("Menu->Color", "Menu->Imagem") \
    X("Menu->Input", "Menu->Entrada") \
    X("Menu->Output", "Menu->Saida") \
    X("Menu->Screen", "Menu->Tela") \
    X("M>Sys>SvAv Set", "Entradas AV/SV") \
    X("M>ACE Settings", "Ajustes do ACE") \
    X("M>Filters", "Filtros de Video") \
    X("M>I2P Settings", "Ajustes do I2P") \
    X("I2P Settings>", "Ajustes do I2P >") \
    X("Video Filters>", "Filtros de Video >") \
    X("ACE Settings >", "Ajustes do ACE >") \
    X("Profile", "Perfil") \
    /* ---- SV/AV (ADV7280) ---- */ \
    X("I2P Settings", "Ajustes do I2P") \
    X("Video Filters", "Filtros de Video") \
    X("ACE Settings", "Ajustes do ACE") \
    X("Brightness", "Brilho") \
    X("Contrast", "Contraste") \
    X("Saturation", "Saturacao") \
    X("Hue", "Matiz") \
    X("Default", "Padrao") \
    X("Enable", "Ativar") \
    X("Enable I2P/2X", "Ativar I2P/2X") \
    X("Smooth", "Suavizacao") \
    X("Luma Gain", "Ganho de Luma") \
    X("Chroma Gain", "Ganho de Croma") \
    X("Chroma Max", "Croma Maximo") \
    X("Gamma Gain", "Ganho de Gama") \
    X("Response Spd", "Velocidade") \
    X("Y Filter", "Filtro Y") \
    X("C Filter", "Filtro C") \
    X("Override", "Modo Manual") \
    X("Bandwidth", "Banda Passante") \
    X("Luma Mode", "Modo de Luma") \
    X("Chroma Mode", "Modo de Croma") \
    X("Chroma Taps", "Linhas de Croma") \
    X("AutoNarrow", "AutoBaixa") \
    X("--AutoWide", "--AutoAlta") \
    X("Wideband", "Ampla") \
    X("Narrow", "Baixa") \
    X("Medium", "Media") \
    X("--Wide", "--Alta") \
    X("Widest", "Maxima") \
    X("FixedTop", "FixoTopo") \
    X("FixedAll", "FixoTudo") \
    X("FixedBot", "FixoBase") \
    X("----None", "--Nenhum") \
    X("Adaptive", "Dinamico") \
    /* ---- picture ---- */ \
    X("Red", "Vermelho") \
    X("Green", "Verde") \
    X("Blue", "Azul") \
    X("ADC gain", "Ganho do ADC") \
    X("Line filter", "Filtro de Linha") \
    X("Sharpness", "Nitidez") \
    X("LOCKED", "TRAVADO") \
    X("Step response", "Nitidez de Cor") \
    X("Y gain", "Ganho de Y") \
    X("Y Gain", "Ganho de Y") \
    X("Color", "Cor") \
    X("Default Color", "Cor Padrao") \
    /* ---- screen ---- */ \
    X("Move", "Mover") \
    X("Scale", "Escala") \
    X("Borders", "Bordas") \
    X("Full height", "Altura Total") \
    X("Center", "Centralizar") \
    X("Reset scale", "Redefinir Escala") \
    /* ---- system ---- */ \
    X("Matched presets", "Preset Por Sinal") \
    X("Deinterlace", "Desentrelacar") \
    X("Force 50 / 60Hz", "Forcar 50/60Hz") \
    X("Force 50Hz to 60Hz", "Forcar 50 Para 60Hz") \
    X("Lock Method", "Modo de Trava") \
    X("Lock method", "Travamento") \
    X("1Vtotal only", "So 1Vtotal") \
    X("ADC calibration", "Calibrar ADC") \
    X("Frame Time Lock", "Trava de Quadro") \
    X("Frame Time lock", "Trava de Quadro") \
    X("EnableFrameTimeLock", "Gerador de Clock") \
    X("Clock generator", "Gerador de Clock") \
    X("HDMI Limited Range", "HDMI Limitado") \
    X("All", "Todos") \
    /* ---- preferences ---- */ \
    X("Theme", "Tema") \
    X("Mute", "Mudo") \
    X("MUTE", "MUDO") \
    X("MUTE ON", "MUDO ON") \
    X("MUTE OFF", "MUDO OFF") \
    X("Dark", "Escuro") \
    X("Light", "Claro") \
    X("---Dark", "-Escuro") \
    X("--Light", "--Claro") \
    X("Classic", "Classico") \
    X("Unknown", "Outro") \
    /* ---- developer ---- */ \
    X("MEM left/right", "Posicao MEM") \
    X("HS left/right", "Posicao HS") \
    X("Debug view", "Depuracao") \
    X("ADC filter", "Filtro do ADC") \
    X("Freeze capture", "Congelar Captura") \
    X("Resync HTotal", "Ajustar HTotal") \
    X("Cycle SDRAM", "Ciclar SDRAM") \
    X("PLL div", "Divisor PLL") \
    X("PLL div++", "Divisor PLL++") \
    X("Invert Sync", "Inverter Sync") \
    X("Oversampling", "Amostragem") \
    X("SOG Level--", "Nivel SOG--") \
    X("Hard pixels", "Pixels Duros") \
    X("Fit 4:3", "Quadro 4:3") \
    /* ---- info / profile / misc ---- */ \
    X("--- GBS-C Pro Versions ---", "--- Versoes GBS-C Pro ---") \
    X("Format:", "Formato") \
    X("Setting", "Ajuste") \
    X("Line input volume", "Volume da Entrada") \
    X("Input:", "Fonte:") \
    X("Output:", "Saida:") \
    X("No Signal", "Sem sinal") \
    X("Load:", "Abrir:") \
    X("Save:", "Salvar") \
    X("Current:", "Atual:") \
    X("None", "Nenhum") \
    X("profile", "Perfil") \
    X("saving", "Salvar") \
    X("Downscale", "Reduzir") \
    X("bypass", "Direto") \
    X("Press to exit", "Pressione para sair")

// Flash blob: "en\0pt\0en\0pt\0...\0"
#define X(en, pt) en "\0" pt "\0"
static const char i18nBlob[] PROGMEM = I18N_TABLE "";
#undef X

#define I18N_BUFS 4
#define I18N_BUF_LEN 48
static char i18nBuf[I18N_BUFS][I18N_BUF_LEN];
static uint8_t i18nBufIdx = 0;

// English: every word of a known label starts with a capital, except small words
static bool enSmallWord(const char *w, size_t n)
{
    static const char *const small[] = { "of", "to", "the", "and", "or", "in", "on" };
    for (uint8_t i = 0; i < sizeof(small) / sizeof(small[0]); i++)
        if (strlen(small[i]) == n && strncmp(small[i], w, n) == 0)
            return true;
    return false;
}

static const char *enTitle(const char *en)
{
    char *buf = i18nBuf[i18nBufIdx++ % I18N_BUFS];
    strncpy(buf, en, I18N_BUF_LEN - 1);
    buf[I18N_BUF_LEN - 1] = '\0';
    char *p = buf;
    while (*p) {
        char *w = p;
        while (*p && *p != ' ')
            p++;
        char *c = w;
        while (c < p && !isalnum((unsigned char)*c))
            c++;
        if (c < p && *c >= 'a' && *c <= 'z' && !enSmallWord(c, p - c))
            *c = *c - 'a' + 'A';
        while (*p == ' ')
            p++;
    }
    return buf;
}

const char *tr(const char *en)
{
    if (en == nullptr || *en == '\0')
        return en;

    const char *p = i18nBlob;
    while (pgm_read_byte(p) != '\0') {
        const char *pt = p + strlen_P(p) + 1;
        if (strcmp_P(en, p) == 0) {
            if (uiLang == LANG_EN) {
                // sentences keep their case; only menu items are title case
                if (strcmp(en, "Reset all settings to") == 0 || strcmp(en, "factory defaults") == 0 ||
                    strcmp(en, "Press to exit") == 0)
                    return en;
                return enTitle(en);
            }
            char *buf = i18nBuf[i18nBufIdx++ % I18N_BUFS];
            strncpy_P(buf, pt, I18N_BUF_LEN - 1);
            buf[I18N_BUF_LEN - 1] = '\0';
            return buf;
        }
        p = pt + strlen_P(pt) + 1;
    }
    return en;
}

const char *i18nLangName(uint8_t lang)
{
    return lang == LANG_PT ? "PT-BR" : "EN-US";
}

void i18nLoad()
{
    uiLang = LANG_PT; // firmware default; /lang.txt overrides it
    File f = LittleFS.open("/lang.txt", "r");
    if (f) {
        int c = f.read() - '0';
        if (c >= 0 && c < LANG_COUNT)
            uiLang = (uint8_t)c;
        f.close();
    }
}

void i18nSave()
{
    File f = LittleFS.open("/lang.txt", "w");
    if (f) {
        f.write('0' + uiLang);
        f.close();
    }
}

uint8_t i18nNext()
{
    uiLang = (uiLang + 1) % LANG_COUNT;
    i18nSave();
    return uiLang;
}

// ---- bitmap translations (generated list in OLEDMenuTranslations_pt.h) ----
struct I18nBitmap {
    const uint8_t *en;
    uint16_t enW, enH;
    const uint8_t *pt;
    uint16_t ptW, ptH;
};

#define B(name) { name, name##_WIDTH, name##_HEIGHT, name##_PT, name##_PT_WIDTH, name##_PT_HEIGHT },
static const I18nBitmap i18nBitmaps[] = { I18N_BITMAP_LIST };
#undef B

const uint8_t *i18nBitmap(const uint8_t *bits, uint16_t &w, uint16_t &h)
{
    if (uiLang != LANG_PT)
        return bits;
    for (size_t i = 0; i < sizeof(i18nBitmaps) / sizeof(i18nBitmaps[0]); i++) {
        const I18nBitmap &b = i18nBitmaps[i];
        if (b.enW != w || b.enH != h)
            continue;
        // Header arrays are internal to each translation unit, so compare contents, not addresses.
        size_t n = ((size_t)(w + 7) / 8) * h;
        bool same = true;
        for (size_t k = 0; k < n && same; k++)
            same = pgm_read_byte(bits + k) == pgm_read_byte(b.en + k);
        if (same) {
            w = b.ptW;
            h = b.ptH;
            return b.pt;
        }
    }
    return bits;
}
