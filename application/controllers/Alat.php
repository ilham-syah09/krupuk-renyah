<?php

defined('BASEPATH') or exit('No direct script access allowed');

class Alat extends CI_Controller
{
	public function getSetting()
	{
		$setting = $this->db->get('setting')->row();
		echo $setting->setSuhu;
	}

	public function simpanData()
	{
		$suhu = $this->input->get('suhu');
		$status = $this->input->get('status');

		$this->db->order_by('id', 'desc');
		$dataLama = $this->db->get('sensor', 1)->row();

		if ($dataLama->suhu == $suhu) {
			echo 'Data masih sama';
		} else {
			$data = [
				'suhu' => $suhu,
				'status' => $status
			];

			$insert = $this->db->insert('sensor', $data);
			if ($insert) {
				echo 'Data berhasil disimpan';
			} else {
				echo 'Server Error!';
			}
		}
	}
}

/* End of file Alat.php */
