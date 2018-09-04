#include "format.h"
#include "../disassembler/algorithm/controlflow.h"

namespace REDasm {

FormatPlugin::FormatPlugin(): Plugin() { m_document.m_format = this; }
ListingDocument *FormatPlugin::document() { return &m_document; }
const SignatureFiles &FormatPlugin::signatures() const { return m_signatures; }
u64 FormatPlugin::addressWidth() const { return this->bits() / 8; }

offset_t FormatPlugin::offset(address_t address) const
{
    const SegmentList& segments = m_document.segments();

    for(auto it = segments.begin(); it != segments.end(); it++)
    {
        const Segment& segment = *it;

        if(segment.contains(address))
            return (address - segment.address) + segment.offset;
    }

    return address;
}

Analyzer* FormatPlugin::createAnalyzer(DisassemblerAPI *disassembler, const SignatureFiles& signatures) const { return new Analyzer(disassembler, signatures); }
DisassemblerAlgorithm *FormatPlugin::createAlgorithm(DisassemblerAPI *disassembler, AssemblerPlugin *assemblerplugin) const { return new DisassemblerControlFlow(disassembler, assemblerplugin); }
u32 FormatPlugin::flags() const { return FormatFlags::None; }
endianness_t FormatPlugin::endianness() const { return Endianness::LittleEndian; /* Use LE by default */ }
bool FormatPlugin::isBinary() const { return this->flags() & FormatFlags::Binary; }
bool FormatPlugin::load(u8 *format) { RE_UNUSED(format); return false; }

}
