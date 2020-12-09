/**
 * @file p5-regalloc.c
 * @brief Compiler phase 5: register allocation
 * @authors Philip Archer and Xinzhe He
 * @date December 9, 2020
 */
#include "p5-regalloc.h"

/**
 * @brief Maximum number of physical registers
 */
#define MAX_PHYSICAL_REGS 32

/**
 * @brief Insert a store instruction to spill a register to the stack
 * 
 * We need to allocate a new slot in the stack from for the current
 * function, so we need a reference to the local allocator instruction.
 * This instruction will always be the third instruction in a function
 * and will be of the form "add SP, -X => SP" where X is the current
 * stack frame size.
 * 
 * @param pr Physical register id that should be spilled
 * @param prev_insn Reference to an instruction; the new instruction will be
 * inserted directly after this one
 * @param local_allocator Reference to the local frame allocator instruction
 * @returns BP-based offset where the register was spilled
 */
int insert_spill(int pr, ILOCInsn* prev_insn, ILOCInsn* local_allocator)
{
    /* adjust stack frame size to add new spill slot */
    int bp_offset = local_allocator->op[1].imm - WORD_SIZE;
    local_allocator->op[1].imm = bp_offset;

    /* create store instruction */
    ILOCInsn* new_insn = ILOCInsn_new_3op(STORE_AI,
            register_with_id(pr), base_register(), int_const(bp_offset));

    /* insert into code */
    new_insn->next = prev_insn->next;
    prev_insn->next = new_insn;

    return bp_offset;
}

/**
 * @brief Insert a load instruction to load a spilled register
 * 
 * @param bp_offset BP-based offset where the register value is spilled
 * @param pr Physical register where the value should be loaded
 * @param prev_insn Reference to an instruction; the new instruction will be
 * inserted directly after this one
 */
void insert_load(int bp_offset, int pr, ILOCInsn* prev_insn)
{
    /* create load instruction */
    ILOCInsn* new_insn = ILOCInsn_new_3op(LOAD_AI,
            base_register(), int_const(bp_offset), register_with_id(pr));

    /* insert into code */
    new_insn->next = prev_insn->next;
    prev_insn->next = new_insn;
}

// Helper arrays
Operand name[];
int offset[];

//spill helper function
void spill (Operand pr)
{
	// emit store from pr onto stack at offset x
	//x = offset[name[pr]];
	//name[pr] = INVALID;
}

//dist helper function
void dist (Operand vr)
{
	//return index of instruction where vr is next used
}

//allocate helper function
void allocate (Operand vr)
{
	/*if (name[pr] == INVALID)
	{
		name[pr] = vr;
		return pr;
	}
	else
	{
		// find pr that maximizes next[pr]
		spill(pr);
		name[pr] = vr;
		return pr;
	}*/
}

//ensure helper function
void ensure (Operand vr)
{
	/*if (name[pr] == vr) //for some pr
	{
		return pr;
	}
	else
	{
		pr = allocate(vr);
		if (offset[vr])
		{
			// emit load into pr from offset[vr]
		}
		return pr;
	}*/
}

void allocate_registers (InsnList* list, int num_physical_registers)
{
	if (list == NULL)
	{
		return;
	}
	
	//allocate_registers(block)
	FOR_EACH(ILOCInsn*, i, list)
	{
		ILOCInsn* read = ILOCInsn_get_read_registers(i);
		Operand write = ILOCInsn_get_write_register(i);

		//FOR_EACH(virtual_register, vr, read->op)
		//{
			// pr = ensure(vr);
			// replace vr with pr in i
			
			/*if (dist(vr) == INFINITY)
			{
				name[pr] = INVALID; // free pr
			}*/
		//}
		
		/*FOR_EACH(virtual_register, vr, write)
		{
			// pr = allocate(vr);
			// replace vr with pr in i
		}*/
		
		//spill section
		/*if (i->form == CALL)
		{
			// for each pr where name[pr] != INVALID
				// spill(pr);
		}*/
	}
}
