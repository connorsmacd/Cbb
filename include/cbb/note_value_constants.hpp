#ifndef IEME_NOTE_VALUE_CONSTANTS_HPP
#define IEME_NOTE_VALUE_CONSTANTS_HPP

#include <cbb/note_value.hpp>


namespace cbb {


static constexpr auto _256th_note = note_value(numbers::one_256th);
static constexpr auto _128th_note = note_value(numbers::one_128th);
static constexpr auto _64th_note = note_value(numbers::one_64th);
static constexpr auto _32nd_note = note_value(numbers::one_32nd);
static constexpr auto _16th_note = note_value(numbers::one_16th);
static constexpr auto _8th_note = note_value(numbers::one_8th);
static constexpr auto quarter_note = note_value(numbers::one_quarter);
static constexpr auto half_note = note_value(numbers::one_half);
static constexpr auto whole_note = note_value(numbers::_1);
static constexpr auto double_whole_note = note_value(numbers::_2);
static constexpr auto quadruple_whole_note = note_value(numbers::_4);
static constexpr auto octuple_whole_note = note_value(numbers::_8);

static constexpr auto demisemihemidemisemiquaver = _256th_note;
static constexpr auto semihemidemisemiquaver = _128th_note;
static constexpr auto hemidemisemiquaver = _64th_note;
static constexpr auto demisemiquaver = _32nd_note;
static constexpr auto semiquaver = _16th_note;
static constexpr auto quaver = _8th_note;
static constexpr auto crotchet = quarter_note;
static constexpr auto minim = half_note;
static constexpr auto semibreve = whole_note;
static constexpr auto breve = double_whole_note;
static constexpr auto longa = quadruple_whole_note;
static constexpr auto maxima = octuple_whole_note;

static constexpr auto triplet_256th_note = _256th_note.with(tuplet::triplet);
static constexpr auto triplet_128th_note = _128th_note.with(tuplet::triplet);
static constexpr auto triplet_64th_note = _64th_note.with(tuplet::triplet);
static constexpr auto triplet_32nd_note = _32nd_note.with(tuplet::triplet);
static constexpr auto triplet_16th_note = _16th_note.with(tuplet::triplet);
static constexpr auto triplet_8th_note = _8th_note.with(tuplet::triplet);
static constexpr auto triplet_quarter_note = quarter_note.with(tuplet::triplet);
static constexpr auto triplet_half_note = half_note.with(tuplet::triplet);
static constexpr auto triplet_whole_note = whole_note.with(tuplet::triplet);
static constexpr auto triplet_double_whole_note
  = double_whole_note.with(tuplet::triplet);
static constexpr auto triplet_quadruple_whole_note
  = quadruple_whole_note.with(tuplet::triplet);
static constexpr auto triplet_octuple_whole_note
  = octuple_whole_note.with(tuplet::triplet);

static constexpr auto triplet_demisemihemidemisemiquaver = triplet_256th_note;
static constexpr auto triplet_semihemidemisemiquaver = triplet_128th_note;
static constexpr auto triplet_hemidemisemiquaver = triplet_64th_note;
static constexpr auto triplet_demisemiquaver = triplet_32nd_note;
static constexpr auto triplet_semiquaver = triplet_16th_note;
static constexpr auto triplet_quaver = triplet_8th_note;
static constexpr auto triplet_crotchet = triplet_quarter_note;
static constexpr auto triplet_minim = triplet_half_note;
static constexpr auto triplet_semibreve = triplet_whole_note;
static constexpr auto triplet_breve = triplet_double_whole_note;
static constexpr auto triplet_longa = triplet_quadruple_whole_note;
static constexpr auto triplet_maxima = triplet_octuple_whole_note;


} // namespace cbb


#endif
