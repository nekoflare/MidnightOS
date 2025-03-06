//
// Created by Neko on 20.01.2025.
//
#include "idt.h"

extern void idt_isr0();
extern void idt_isr1();
extern void idt_isr2();
extern void idt_isr3();
extern void idt_isr4();
extern void idt_isr5();
extern void idt_isr6();
extern void idt_isr7();
extern void idt_isr8();
extern void idt_isr9();
extern void idt_isr10();
extern void idt_isr11();
extern void idt_isr12();
extern void idt_isr13();
extern void idt_isr14();
extern void idt_isr15();
extern void idt_isr16();
extern void idt_isr17();
extern void idt_isr18();
extern void idt_isr19();
extern void idt_isr20();
extern void idt_isr21();
extern void idt_isr22();
extern void idt_isr23();
extern void idt_isr24();
extern void idt_isr25();
extern void idt_isr26();
extern void idt_isr27();
extern void idt_isr28();
extern void idt_isr29();
extern void idt_isr30();
extern void idt_isr31();
extern void idt_isr32();
extern void idt_isr33();
extern void idt_isr34();
extern void idt_isr35();
extern void idt_isr36();
extern void idt_isr37();
extern void idt_isr38();
extern void idt_isr39();
extern void idt_isr40();
extern void idt_isr41();
extern void idt_isr42();
extern void idt_isr43();
extern void idt_isr44();
extern void idt_isr45();
extern void idt_isr46();
extern void idt_isr47();
extern void idt_isr48();
extern void idt_isr49();
extern void idt_isr50();
extern void idt_isr51();
extern void idt_isr52();
extern void idt_isr53();
extern void idt_isr54();
extern void idt_isr55();
extern void idt_isr56();
extern void idt_isr57();
extern void idt_isr58();
extern void idt_isr59();
extern void idt_isr60();
extern void idt_isr61();
extern void idt_isr62();
extern void idt_isr63();
extern void idt_isr64();
extern void idt_isr65();
extern void idt_isr66();
extern void idt_isr67();
extern void idt_isr68();
extern void idt_isr69();
extern void idt_isr70();
extern void idt_isr71();
extern void idt_isr72();
extern void idt_isr73();
extern void idt_isr74();
extern void idt_isr75();
extern void idt_isr76();
extern void idt_isr77();
extern void idt_isr78();
extern void idt_isr79();
extern void idt_isr80();
extern void idt_isr81();
extern void idt_isr82();
extern void idt_isr83();
extern void idt_isr84();
extern void idt_isr85();
extern void idt_isr86();
extern void idt_isr87();
extern void idt_isr88();
extern void idt_isr89();
extern void idt_isr90();
extern void idt_isr91();
extern void idt_isr92();
extern void idt_isr93();
extern void idt_isr94();
extern void idt_isr95();
extern void idt_isr96();
extern void idt_isr97();
extern void idt_isr98();
extern void idt_isr99();
extern void idt_isr100();
extern void idt_isr101();
extern void idt_isr102();
extern void idt_isr103();
extern void idt_isr104();
extern void idt_isr105();
extern void idt_isr106();
extern void idt_isr107();
extern void idt_isr108();
extern void idt_isr109();
extern void idt_isr110();
extern void idt_isr111();
extern void idt_isr112();
extern void idt_isr113();
extern void idt_isr114();
extern void idt_isr115();
extern void idt_isr116();
extern void idt_isr117();
extern void idt_isr118();
extern void idt_isr119();
extern void idt_isr120();
extern void idt_isr121();
extern void idt_isr122();
extern void idt_isr123();
extern void idt_isr124();
extern void idt_isr125();
extern void idt_isr126();
extern void idt_isr127();
extern void idt_isr128();
extern void idt_isr129();
extern void idt_isr130();
extern void idt_isr131();
extern void idt_isr132();
extern void idt_isr133();
extern void idt_isr134();
extern void idt_isr135();
extern void idt_isr136();
extern void idt_isr137();
extern void idt_isr138();
extern void idt_isr139();
extern void idt_isr140();
extern void idt_isr141();
extern void idt_isr142();
extern void idt_isr143();
extern void idt_isr144();
extern void idt_isr145();
extern void idt_isr146();
extern void idt_isr147();
extern void idt_isr148();
extern void idt_isr149();
extern void idt_isr150();
extern void idt_isr151();
extern void idt_isr152();
extern void idt_isr153();
extern void idt_isr154();
extern void idt_isr155();
extern void idt_isr156();
extern void idt_isr157();
extern void idt_isr158();
extern void idt_isr159();
extern void idt_isr160();
extern void idt_isr161();
extern void idt_isr162();
extern void idt_isr163();
extern void idt_isr164();
extern void idt_isr165();
extern void idt_isr166();
extern void idt_isr167();
extern void idt_isr168();
extern void idt_isr169();
extern void idt_isr170();
extern void idt_isr171();
extern void idt_isr172();
extern void idt_isr173();
extern void idt_isr174();
extern void idt_isr175();
extern void idt_isr176();
extern void idt_isr177();
extern void idt_isr178();
extern void idt_isr179();
extern void idt_isr180();
extern void idt_isr181();
extern void idt_isr182();
extern void idt_isr183();
extern void idt_isr184();
extern void idt_isr185();
extern void idt_isr186();
extern void idt_isr187();
extern void idt_isr188();
extern void idt_isr189();
extern void idt_isr190();
extern void idt_isr191();
extern void idt_isr192();
extern void idt_isr193();
extern void idt_isr194();
extern void idt_isr195();
extern void idt_isr196();
extern void idt_isr197();
extern void idt_isr198();
extern void idt_isr199();
extern void idt_isr200();
extern void idt_isr201();
extern void idt_isr202();
extern void idt_isr203();
extern void idt_isr204();
extern void idt_isr205();
extern void idt_isr206();
extern void idt_isr207();
extern void idt_isr208();
extern void idt_isr209();
extern void idt_isr210();
extern void idt_isr211();
extern void idt_isr212();
extern void idt_isr213();
extern void idt_isr214();
extern void idt_isr215();
extern void idt_isr216();
extern void idt_isr217();
extern void idt_isr218();
extern void idt_isr219();
extern void idt_isr220();
extern void idt_isr221();
extern void idt_isr222();
extern void idt_isr223();
extern void idt_isr224();
extern void idt_isr225();
extern void idt_isr226();
extern void idt_isr227();
extern void idt_isr228();
extern void idt_isr229();
extern void idt_isr230();
extern void idt_isr231();
extern void idt_isr232();
extern void idt_isr233();
extern void idt_isr234();
extern void idt_isr235();
extern void idt_isr236();
extern void idt_isr237();
extern void idt_isr238();
extern void idt_isr239();
extern void idt_isr240();
extern void idt_isr241();
extern void idt_isr242();
extern void idt_isr243();
extern void idt_isr244();
extern void idt_isr245();
extern void idt_isr246();
extern void idt_isr247();
extern void idt_isr248();
extern void idt_isr249();
extern void idt_isr250();
extern void idt_isr251();
extern void idt_isr252();
extern void idt_isr253();
extern void idt_isr254();
extern void idt_isr255();

volatile struct KGATE_DESCRIPTOR_64 Idt[256] = {0};

void KiLoadIDTTableEntries()
{
    PREVENT_DOUBLE_INIT
    Idt[0] = KiCreateIDTEntry(&idt_isr0, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[1] = KiCreateIDTEntry(&idt_isr1, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[2] = KiCreateIDTEntry(&idt_isr2, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[3] = KiCreateIDTEntry(&idt_isr3, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[4] = KiCreateIDTEntry(&idt_isr4, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[5] = KiCreateIDTEntry(&idt_isr5, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[6] = KiCreateIDTEntry(&idt_isr6, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[7] = KiCreateIDTEntry(&idt_isr7, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[8] = KiCreateIDTEntry(&idt_isr8, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[9] = KiCreateIDTEntry(&idt_isr9, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                              IDT_NO_IST);
    Idt[10] = KiCreateIDTEntry(&idt_isr10, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[11] = KiCreateIDTEntry(&idt_isr11, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[12] = KiCreateIDTEntry(&idt_isr12, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[13] = KiCreateIDTEntry(&idt_isr13, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[14] = KiCreateIDTEntry(&idt_isr14, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[15] = KiCreateIDTEntry(&idt_isr15, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[16] = KiCreateIDTEntry(&idt_isr16, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[17] = KiCreateIDTEntry(&idt_isr17, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[18] = KiCreateIDTEntry(&idt_isr18, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[19] = KiCreateIDTEntry(&idt_isr19, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[20] = KiCreateIDTEntry(&idt_isr20, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[21] = KiCreateIDTEntry(&idt_isr21, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[22] = KiCreateIDTEntry(&idt_isr22, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[23] = KiCreateIDTEntry(&idt_isr23, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[24] = KiCreateIDTEntry(&idt_isr24, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[25] = KiCreateIDTEntry(&idt_isr25, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[26] = KiCreateIDTEntry(&idt_isr26, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[27] = KiCreateIDTEntry(&idt_isr27, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[28] = KiCreateIDTEntry(&idt_isr28, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[29] = KiCreateIDTEntry(&idt_isr29, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[30] = KiCreateIDTEntry(&idt_isr30, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[31] = KiCreateIDTEntry(&idt_isr31, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[32] = KiCreateIDTEntry(&idt_isr32, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[33] = KiCreateIDTEntry(&idt_isr33, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[34] = KiCreateIDTEntry(&idt_isr34, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[35] = KiCreateIDTEntry(&idt_isr35, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[36] = KiCreateIDTEntry(&idt_isr36, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[37] = KiCreateIDTEntry(&idt_isr37, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[38] = KiCreateIDTEntry(&idt_isr38, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[39] = KiCreateIDTEntry(&idt_isr39, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[40] = KiCreateIDTEntry(&idt_isr40, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[41] = KiCreateIDTEntry(&idt_isr41, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[42] = KiCreateIDTEntry(&idt_isr42, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[43] = KiCreateIDTEntry(&idt_isr43, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[44] = KiCreateIDTEntry(&idt_isr44, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[45] = KiCreateIDTEntry(&idt_isr45, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[46] = KiCreateIDTEntry(&idt_isr46, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[47] = KiCreateIDTEntry(&idt_isr47, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[48] = KiCreateIDTEntry(&idt_isr48, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[49] = KiCreateIDTEntry(&idt_isr49, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[50] = KiCreateIDTEntry(&idt_isr50, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[51] = KiCreateIDTEntry(&idt_isr51, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[52] = KiCreateIDTEntry(&idt_isr52, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[53] = KiCreateIDTEntry(&idt_isr53, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[54] = KiCreateIDTEntry(&idt_isr54, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[55] = KiCreateIDTEntry(&idt_isr55, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[56] = KiCreateIDTEntry(&idt_isr56, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[57] = KiCreateIDTEntry(&idt_isr57, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[58] = KiCreateIDTEntry(&idt_isr58, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[59] = KiCreateIDTEntry(&idt_isr59, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[60] = KiCreateIDTEntry(&idt_isr60, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[61] = KiCreateIDTEntry(&idt_isr61, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[62] = KiCreateIDTEntry(&idt_isr62, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[63] = KiCreateIDTEntry(&idt_isr63, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[64] = KiCreateIDTEntry(&idt_isr64, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[65] = KiCreateIDTEntry(&idt_isr65, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[66] = KiCreateIDTEntry(&idt_isr66, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[67] = KiCreateIDTEntry(&idt_isr67, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[68] = KiCreateIDTEntry(&idt_isr68, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[69] = KiCreateIDTEntry(&idt_isr69, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[70] = KiCreateIDTEntry(&idt_isr70, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[71] = KiCreateIDTEntry(&idt_isr71, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[72] = KiCreateIDTEntry(&idt_isr72, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[73] = KiCreateIDTEntry(&idt_isr73, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[74] = KiCreateIDTEntry(&idt_isr74, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[75] = KiCreateIDTEntry(&idt_isr75, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[76] = KiCreateIDTEntry(&idt_isr76, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[77] = KiCreateIDTEntry(&idt_isr77, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[78] = KiCreateIDTEntry(&idt_isr78, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[79] = KiCreateIDTEntry(&idt_isr79, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[80] = KiCreateIDTEntry(&idt_isr80, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[81] = KiCreateIDTEntry(&idt_isr81, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[82] = KiCreateIDTEntry(&idt_isr82, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[83] = KiCreateIDTEntry(&idt_isr83, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[84] = KiCreateIDTEntry(&idt_isr84, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[85] = KiCreateIDTEntry(&idt_isr85, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[86] = KiCreateIDTEntry(&idt_isr86, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[87] = KiCreateIDTEntry(&idt_isr87, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[88] = KiCreateIDTEntry(&idt_isr88, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[89] = KiCreateIDTEntry(&idt_isr89, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[90] = KiCreateIDTEntry(&idt_isr90, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[91] = KiCreateIDTEntry(&idt_isr91, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[92] = KiCreateIDTEntry(&idt_isr92, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[93] = KiCreateIDTEntry(&idt_isr93, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[94] = KiCreateIDTEntry(&idt_isr94, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[95] = KiCreateIDTEntry(&idt_isr95, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[96] = KiCreateIDTEntry(&idt_isr96, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[97] = KiCreateIDTEntry(&idt_isr97, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[98] = KiCreateIDTEntry(&idt_isr98, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[99] = KiCreateIDTEntry(&idt_isr99, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                               IDT_NO_IST);
    Idt[100] = KiCreateIDTEntry(&idt_isr100, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[101] = KiCreateIDTEntry(&idt_isr101, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[102] = KiCreateIDTEntry(&idt_isr102, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[103] = KiCreateIDTEntry(&idt_isr103, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[104] = KiCreateIDTEntry(&idt_isr104, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[105] = KiCreateIDTEntry(&idt_isr105, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[106] = KiCreateIDTEntry(&idt_isr106, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[107] = KiCreateIDTEntry(&idt_isr107, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[108] = KiCreateIDTEntry(&idt_isr108, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[109] = KiCreateIDTEntry(&idt_isr109, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[110] = KiCreateIDTEntry(&idt_isr110, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[111] = KiCreateIDTEntry(&idt_isr111, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[112] = KiCreateIDTEntry(&idt_isr112, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[113] = KiCreateIDTEntry(&idt_isr113, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[114] = KiCreateIDTEntry(&idt_isr114, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[115] = KiCreateIDTEntry(&idt_isr115, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[116] = KiCreateIDTEntry(&idt_isr116, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[117] = KiCreateIDTEntry(&idt_isr117, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[118] = KiCreateIDTEntry(&idt_isr118, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[119] = KiCreateIDTEntry(&idt_isr119, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[120] = KiCreateIDTEntry(&idt_isr120, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[121] = KiCreateIDTEntry(&idt_isr121, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[122] = KiCreateIDTEntry(&idt_isr122, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[123] = KiCreateIDTEntry(&idt_isr123, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[124] = KiCreateIDTEntry(&idt_isr124, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[125] = KiCreateIDTEntry(&idt_isr125, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[126] = KiCreateIDTEntry(&idt_isr126, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[127] = KiCreateIDTEntry(&idt_isr127, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[128] = KiCreateIDTEntry(&idt_isr128, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[129] = KiCreateIDTEntry(&idt_isr129, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[130] = KiCreateIDTEntry(&idt_isr130, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[131] = KiCreateIDTEntry(&idt_isr131, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[132] = KiCreateIDTEntry(&idt_isr132, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[133] = KiCreateIDTEntry(&idt_isr133, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[134] = KiCreateIDTEntry(&idt_isr134, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[135] = KiCreateIDTEntry(&idt_isr135, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[136] = KiCreateIDTEntry(&idt_isr136, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[137] = KiCreateIDTEntry(&idt_isr137, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[138] = KiCreateIDTEntry(&idt_isr138, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[139] = KiCreateIDTEntry(&idt_isr139, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[140] = KiCreateIDTEntry(&idt_isr140, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[141] = KiCreateIDTEntry(&idt_isr141, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[142] = KiCreateIDTEntry(&idt_isr142, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[143] = KiCreateIDTEntry(&idt_isr143, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[144] = KiCreateIDTEntry(&idt_isr144, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[145] = KiCreateIDTEntry(&idt_isr145, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[146] = KiCreateIDTEntry(&idt_isr146, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[147] = KiCreateIDTEntry(&idt_isr147, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[148] = KiCreateIDTEntry(&idt_isr148, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[149] = KiCreateIDTEntry(&idt_isr149, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[150] = KiCreateIDTEntry(&idt_isr150, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[151] = KiCreateIDTEntry(&idt_isr151, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[152] = KiCreateIDTEntry(&idt_isr152, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[153] = KiCreateIDTEntry(&idt_isr153, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[154] = KiCreateIDTEntry(&idt_isr154, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[155] = KiCreateIDTEntry(&idt_isr155, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[156] = KiCreateIDTEntry(&idt_isr156, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[157] = KiCreateIDTEntry(&idt_isr157, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[158] = KiCreateIDTEntry(&idt_isr158, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[159] = KiCreateIDTEntry(&idt_isr159, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[160] = KiCreateIDTEntry(&idt_isr160, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[161] = KiCreateIDTEntry(&idt_isr161, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[162] = KiCreateIDTEntry(&idt_isr162, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[163] = KiCreateIDTEntry(&idt_isr163, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[164] = KiCreateIDTEntry(&idt_isr164, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[165] = KiCreateIDTEntry(&idt_isr165, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[166] = KiCreateIDTEntry(&idt_isr166, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[167] = KiCreateIDTEntry(&idt_isr167, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[168] = KiCreateIDTEntry(&idt_isr168, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[169] = KiCreateIDTEntry(&idt_isr169, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[170] = KiCreateIDTEntry(&idt_isr170, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[171] = KiCreateIDTEntry(&idt_isr171, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[172] = KiCreateIDTEntry(&idt_isr172, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[173] = KiCreateIDTEntry(&idt_isr173, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[174] = KiCreateIDTEntry(&idt_isr174, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[175] = KiCreateIDTEntry(&idt_isr175, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[176] = KiCreateIDTEntry(&idt_isr176, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[177] = KiCreateIDTEntry(&idt_isr177, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[178] = KiCreateIDTEntry(&idt_isr178, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[179] = KiCreateIDTEntry(&idt_isr179, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[180] = KiCreateIDTEntry(&idt_isr180, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[181] = KiCreateIDTEntry(&idt_isr181, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[182] = KiCreateIDTEntry(&idt_isr182, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[183] = KiCreateIDTEntry(&idt_isr183, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[184] = KiCreateIDTEntry(&idt_isr184, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[185] = KiCreateIDTEntry(&idt_isr185, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[186] = KiCreateIDTEntry(&idt_isr186, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[187] = KiCreateIDTEntry(&idt_isr187, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[188] = KiCreateIDTEntry(&idt_isr188, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[189] = KiCreateIDTEntry(&idt_isr189, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[190] = KiCreateIDTEntry(&idt_isr190, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[191] = KiCreateIDTEntry(&idt_isr191, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[192] = KiCreateIDTEntry(&idt_isr192, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[193] = KiCreateIDTEntry(&idt_isr193, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[194] = KiCreateIDTEntry(&idt_isr194, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[195] = KiCreateIDTEntry(&idt_isr195, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[196] = KiCreateIDTEntry(&idt_isr196, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[197] = KiCreateIDTEntry(&idt_isr197, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[198] = KiCreateIDTEntry(&idt_isr198, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[199] = KiCreateIDTEntry(&idt_isr199, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[200] = KiCreateIDTEntry(&idt_isr200, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[201] = KiCreateIDTEntry(&idt_isr201, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[202] = KiCreateIDTEntry(&idt_isr202, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[203] = KiCreateIDTEntry(&idt_isr203, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[204] = KiCreateIDTEntry(&idt_isr204, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[205] = KiCreateIDTEntry(&idt_isr205, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[206] = KiCreateIDTEntry(&idt_isr206, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[207] = KiCreateIDTEntry(&idt_isr207, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[208] = KiCreateIDTEntry(&idt_isr208, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[209] = KiCreateIDTEntry(&idt_isr209, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[210] = KiCreateIDTEntry(&idt_isr210, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[211] = KiCreateIDTEntry(&idt_isr211, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[212] = KiCreateIDTEntry(&idt_isr212, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[213] = KiCreateIDTEntry(&idt_isr213, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[214] = KiCreateIDTEntry(&idt_isr214, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[215] = KiCreateIDTEntry(&idt_isr215, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[216] = KiCreateIDTEntry(&idt_isr216, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[217] = KiCreateIDTEntry(&idt_isr217, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[218] = KiCreateIDTEntry(&idt_isr218, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[219] = KiCreateIDTEntry(&idt_isr219, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[220] = KiCreateIDTEntry(&idt_isr220, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[221] = KiCreateIDTEntry(&idt_isr221, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[222] = KiCreateIDTEntry(&idt_isr222, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[223] = KiCreateIDTEntry(&idt_isr223, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[224] = KiCreateIDTEntry(&idt_isr224, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[225] = KiCreateIDTEntry(&idt_isr225, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[226] = KiCreateIDTEntry(&idt_isr226, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[227] = KiCreateIDTEntry(&idt_isr227, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[228] = KiCreateIDTEntry(&idt_isr228, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[229] = KiCreateIDTEntry(&idt_isr229, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[230] = KiCreateIDTEntry(&idt_isr230, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[231] = KiCreateIDTEntry(&idt_isr231, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[232] = KiCreateIDTEntry(&idt_isr232, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[233] = KiCreateIDTEntry(&idt_isr233, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[234] = KiCreateIDTEntry(&idt_isr234, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[235] = KiCreateIDTEntry(&idt_isr235, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[236] = KiCreateIDTEntry(&idt_isr236, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[237] = KiCreateIDTEntry(&idt_isr237, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[238] = KiCreateIDTEntry(&idt_isr238, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[239] = KiCreateIDTEntry(&idt_isr239, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[240] = KiCreateIDTEntry(&idt_isr240, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[241] = KiCreateIDTEntry(&idt_isr241, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[242] = KiCreateIDTEntry(&idt_isr242, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[243] = KiCreateIDTEntry(&idt_isr243, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[244] = KiCreateIDTEntry(&idt_isr244, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[245] = KiCreateIDTEntry(&idt_isr245, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[246] = KiCreateIDTEntry(&idt_isr246, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[247] = KiCreateIDTEntry(&idt_isr247, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[248] = KiCreateIDTEntry(&idt_isr248, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[249] = KiCreateIDTEntry(&idt_isr249, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[250] = KiCreateIDTEntry(&idt_isr250, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[251] = KiCreateIDTEntry(&idt_isr251, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[252] = KiCreateIDTEntry(&idt_isr252, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[253] = KiCreateIDTEntry(&idt_isr253, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[254] = KiCreateIDTEntry(&idt_isr254, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
    Idt[255] = KiCreateIDTEntry(&idt_isr255, IDT_DEFAULT_SEGMENT, IDT_GATE_TYPE_INTERRUPT, IDT_DPL_RING_0, IDT_PRESENT,
                                IDT_NO_IST);
}