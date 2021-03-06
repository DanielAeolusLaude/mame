// license:BSD-3-Clause
// copyright-holders:Fabio Priuli
#ifndef __INTV_VOICE_H
#define __INTV_VOICE_H

#include "slot.h"
#include "rom.h"
#include "sound/sp0256.h"


// ======================> intv_voice_device

class intv_voice_device : public intv_rom_device
{
public:
	// construction/destruction
	intv_voice_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// device-level overrides
	virtual void device_start();
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual const rom_entry *device_rom_region() const;

	// reading and writing
	// actual IntelliVoice access
	virtual DECLARE_READ16_MEMBER(read_speech);
	virtual DECLARE_WRITE16_MEMBER(write_speech);

	// passthru access
	virtual DECLARE_READ16_MEMBER(read_rom04) { return m_subslot->read_rom04(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_rom20) { return m_subslot->read_rom20(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_rom40) { return m_subslot->read_rom40(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_rom48) { return m_subslot->read_rom48(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_rom50) { return m_subslot->read_rom50(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_rom60) { return m_subslot->read_rom60(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_rom70) { return m_subslot->read_rom70(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_rom80)
	{
		if (m_ram88_enabled && offset >= 0x800)
			return m_subslot->read_ram(space, offset & 0x7ff, mem_mask);
		else
			return m_subslot->read_rom80(space, offset, mem_mask);
	}
	virtual DECLARE_READ16_MEMBER(read_rom90) { return m_subslot->read_rom90(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_roma0) { return m_subslot->read_roma0(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_romb0) { return m_subslot->read_romb0(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_romc0) { return m_subslot->read_romc0(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_romd0)
	{
		if (m_ramd0_enabled && offset < 0x800)
			return m_subslot->read_ram(space, offset, mem_mask);
		else
			return m_subslot->read_romd0(space, offset, mem_mask);
	}
	virtual DECLARE_READ16_MEMBER(read_rome0) { return m_subslot->read_rome0(space, offset, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_romf0) { return m_subslot->read_romf0(space, offset, mem_mask); }

	// RAM passthru write
	virtual DECLARE_WRITE16_MEMBER(write_88) { if (m_ram88_enabled) m_subslot->write_ram(space, offset, data, mem_mask); }
	virtual DECLARE_WRITE16_MEMBER(write_d0) { if (m_ramd0_enabled) m_subslot->write_ram(space, offset, data, mem_mask); }
	virtual DECLARE_READ16_MEMBER(read_ram) { return m_subslot->read_ram(space, offset, mem_mask); }
	virtual DECLARE_WRITE16_MEMBER(write_ram) { m_subslot->write_ram(space, offset, data, mem_mask); }

	virtual void late_subslot_setup();

private:
	required_device<sp0256_device> m_speech;
	required_device<intv_cart_slot_device> m_subslot;
	bool m_ramd0_enabled, m_ram88_enabled;
};




// device type definition
extern const device_type INTV_ROM_VOICE;

#endif
